FROM hashicorp/vault:latest
USER root

RUN apk add --no-cache bash curl jq

RUN mkdir -p /vault/policies /vault/scripts /vault/data
COPY config.hcl /vault/config.hcl
COPY entrypoint.sh /vault/scripts/entrypoint.sh
RUN chmod +x /vault/scripts/entrypoint.sh
COPY policy.hcl /vault/policies/policy.hcl

ENTRYPOINT ["/vault/scripts/entrypoint.sh"]
