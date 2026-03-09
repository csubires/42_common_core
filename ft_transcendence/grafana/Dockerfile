FROM grafana/grafana:latest

USER root
RUN apk add --no-cache wget curl bash && \
    mkdir -p /var/log/grafana \
             /etc/grafana/provisioning/dashboards \
             /etc/grafana/provisioning/datasources \
             /var/lib/grafana/dashboards
COPY entrypoint.sh /usr/local/bin/entrypoint.sh
COPY datasource.yml /etc/grafana/provisioning/datasources/datasource.yml
COPY dashboards.yml /etc/grafana/provisioning/dashboards/dashboards.yml
COPY dashboards/ /var/lib/grafana/dashboards/
RUN chmod +x /usr/local/bin/entrypoint.sh

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
