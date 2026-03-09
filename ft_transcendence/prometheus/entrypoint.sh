#!/bin/sh
set -e

start_log_processor() {

    local METRICS_FILE="/tmp/logs.prom"
    local LOGS_DIR="/logs"
    local HTTP_PORT=9100

    process_logs() {
        local TMP_FILE="${METRICS_FILE}.tmp"

        > "$TMP_FILE"

        if [ -d "$LOGS_DIR" ]; then
            find "$LOGS_DIR" -name "*.log" -type f 2>/dev/null | head -5 | while IFS= read -r log_file; do
                local service_name="unknown"
                local file_name=$(basename "$log_file")

                tail -30 "$log_file" 2>/dev/null | while IFS= read -r line; do
                    if [ -n "$line" ]; then
                        safe_line=$(echo "$line" | sed 's/\\/\\\\/g; s/"/\\"/g')
                        echo "log_line{service=\"$service_name\",file=\"$file_name\",content=\"$safe_line\"} 1" >> "$TMP_FILE"
                    fi
                done
            done

            if [ -f "$TMP_FILE" ]; then
                mv "$TMP_FILE" "$METRICS_FILE"
            fi
        fi
    }

    start_log_server() {
        while true; do
            {
                printf "HTTP/1.1 200 OK\r\n"
                printf "Content-Type: text/plain; version=0.0.4\r\n"
                printf "Connection: close\r\n"
                printf "\r\n"
            } | nc -l -p "$HTTP_PORT" -q 1 2>/dev/null || true
        done
    }

    while true; do
        process_logs
        sleep 30
    done &

    start_log_server &
}

start_prometheus() {

    if [ ! -f /etc/prometheus/prometheus.yml ]; then
        exit 1
    fi

    if [ ! -w /prometheus ]; then
        exit 1
    fi

    exec /bin/prometheus \
        --config.file=/etc/prometheus/prometheus.yml \
        --storage.tsdb.path=/prometheus \
        --web.console.libraries=/etc/prometheus/console_libraries \
        --web.console.templates=/etc/prometheus/consoles \
        --web.enable-lifecycle \
        --storage.tsdb.retention.time=7d \
        --storage.tsdb.retention.size=256MB \
        --web.route-prefix=/ \
        --web.enable-admin-api \
        --storage.tsdb.wal-compression &
}

start_prometheus
PROMETHEUS_PID=$!
sleep 5
start_log_processor
LOG_PROCESSOR_PID=$!

cleanup() {
    kill $PROMETHEUS_PID 2>/dev/null
    kill $LOG_PROCESSOR_PID 2>/dev/null
    wait
    exit 0
}

trap cleanup SIGTERM SIGINT
wait $PROMETHEUS_PID $LOG_PROCESSOR_PID
