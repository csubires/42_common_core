#!/bin/bash
set -e

mkdir -p /var/log/grafana /var/lib/grafana/dashboards

if [ ! -f "/etc/grafana/ssl/certificate.pem" ] || [ ! -f "/etc/grafana/ssl/private-key.pem" ]; then
    exit 1
fi

export GF_SERVER_PROTOCOL=https
export GF_SERVER_CERT_FILE=/etc/grafana/ssl/certificate.pem
export GF_SERVER_CERT_KEY=/etc/grafana/ssl/private-key.pem
export GF_SERVER_DOMAIN=localhost
export GF_SERVER_ROOT_URL=https://localhost:3302/
export GF_SECURITY_ALLOW_EMBEDDING=true
export GF_SECURITY_COOKIE_SECURE=true
export GF_SECURITY_COOKIE_SAMESITE=none
export GF_USERS_ALLOW_SIGN_UP=false

cat > /etc/grafana/grafana.ini << EOF
[server]
protocol = https
http_port = 3301
domain = localhost
root_url = https://localhost:3302/
cert_file = /etc/grafana/ssl/certificate.pem
cert_key = /etc/grafana/ssl/private-key.pem
enable_gzip = true

[security]
allow_embedding = true
cookie_secure = true
cookie_samesite = none

[users]
allow_sign_up = false

[analytics]
reporting_enabled = false

[database]
type = sqlite3

[log]
mode = console
level = info
EOF

exec /run.sh "$@"
