#!/bin/bash
set -e

export VAULT_ADDR="http://vault:8200"
export VAULT_TOKEN="root"

vault server \
  -dev \
  -dev-root-token-id="$VAULT_TOKEN" \
  -dev-listen-address="0.0.0.0:8200" &

VAULT_PID=$!

until vault status >/dev/null 2>&1; do
  sleep 1
done

if ! vault secrets list | grep -q '^secret/'; then
  vault secrets enable -path=secret kv-v2
fi

if [ -n "$GITHUB_CLIENT_ID" ] && [ -n "$GITHUB_CLIENT_SECRET" ]; then
  vault kv put secret/oauth/github client_id="$GITHUB_CLIENT_ID" client_secret="$GITHUB_CLIENT_SECRET"
fi

if vault kv get secret/session/config >/dev/null 2>&1; then
  echo "✔ Session secret already exists"
else
    SESSION_SECRET=$(head -c 32 /dev/urandom | xxd -p -c 256)
    vault kv put secret/session/config secret="$SESSION_SECRET"
fi

if vault kv get secret/jwt/config >/dev/null 2>&1; then
  echo "✔ JWT secret already exists"
else
  JWT_SECRET=$(head -c 32 /dev/urandom | xxd -p -c 256)
  vault kv put secret/jwt/config jwt_secret="$JWT_SECRET"
fi

if vault kv get secret/service-token/config >/dev/null 2>&1; then
  echo "✔ Service token already exists"
else
  SERVICE_TOKEN=$(head -c 32 /dev/urandom | xxd -p -c 256)
  vault kv put secret/service-token/config token="$SERVICE_TOKEN"
fi

wait $VAULT_PID
