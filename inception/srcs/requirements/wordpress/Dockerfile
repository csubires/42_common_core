FROM alpine:3.18
RUN apk update && apk add --no-cache \
    php82-fpm \
    php82-json \
    php82-zlib \
    php82-xml \
    php82-xmlwriter \
    php82-simplexml \
    php82-pdo \
    php82-phar \
    php82-openssl \
    php82-pdo_mysql \
    php82-mysqli \
    php82-session \
    php82-iconv \
    php82-mbstring \
    mariadb-client \
    curl \
    sudo \
    bash

RUN rm -rf /var/cache/apk/*

COPY conf/php-fpm.conf /etc/php82/
RUN adduser -DSh /var/www -u 82 -G www-data www-data && \
    echo "www-data ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers && \
    mkdir -p /var/log/php82 && \
    chown -R www-data:www-data /var/log/php82

COPY tools/entrypoint.sh /tmp/
COPY tools/wp-cli.phar /tmp/
RUN chmod +x /tmp/wp-cli.phar && chmod +x /tmp/entrypoint.sh && \
    mv /tmp/wp-cli.phar /usr/local/bin/wp && \
    ln -s /usr/bin/php82 /usr/bin/php && \
    ln -s /usr/sbin/php-fpm82 /usr/sbin/php-fpm

ENTRYPOINT ["/tmp/entrypoint.sh"]
