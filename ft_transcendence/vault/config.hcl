disable_mlock = true
ui = true

storage "file" {
  path = "/vault/data"
}

listener "tcp" {
  address = "0.0.0.0:8200"
  tls_disable = false
  tls_cert_file = "/vault/ssl/certificate.pem"
  tls_key_file = "/vault/ssl/private-key.pem"
}

api_addr = "https://localhost:8200"
cluster_addr = "https://localhost:8201"

log_level = "warn"
