FROM prom/prometheus:latest

USER root
RUN mkdir -p /etc/prometheus /var/log/prometheus /logs
COPY prometheus.yml /etc/prometheus/prometheus.yml
COPY entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh
USER nobody

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
