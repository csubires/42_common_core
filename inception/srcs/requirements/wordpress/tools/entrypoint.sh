#!/bin/bash

echo "file_uploads = On" > /etc/php82/conf.d/memory.ini
echo "upload_max_filesize = 164M" >> /etc/php82/conf.d/memory.ini
echo "post_max_size = 64M" >> /etc/php82/conf.d/memory.ini
echo "max_execution_time = 600" >> /etc/php82/conf.d/memory.ini
echo "memory_limit = 512M" >> /etc/php82/conf.d/memory.ini

echo "opcache.enable=1" > /etc/php82/conf.d/opcache.ini
echo "opcache.memory_consumption=128" >> /etc/php82/conf.d/opcache.ini
touch /var/log/php82/error.log

wait_for_db()
{
    echo "Testing DB connection with: ${MYSQL_USER}@${MYSQL_HOST}"
    while ! mysqladmin ping -h"${MYSQL_HOST}" -u"${MYSQL_USER}" -p"${MYSQL_PASSWORD}" --silent; do
        echo "Waiting for MariaDB..."
        sleep 3
    done
}

wait_for_db

cd /var/www/html

# Download WordPress if not exists
if [ ! -f "wp-config.php" ]; then
    echo "Downloading WordPress..."
    wp core download --allow-root
    # Verify download
    if [ -f "wp-config-sample.php" ]; then
        echo "Creating wp-config.php..."
        wp config create \
            --dbname=$MYSQL_DATABASE \
            --dbuser=$MYSQL_USER \
            --dbpass=$MYSQL_PASSWORD \
            --dbhost=$MYSQL_HOST \
            --allow-root

        echo "Installing WordPress..."
        wp core install \
            --url=$DOMAIN_NAME \
            --title="$WP_TITLE" \
            --admin_user=$WP_ADMIN_USR \
            --admin_password=$WP_ADMIN_PWD \
            --admin_email=$WP_ADMIN_EMAIL \
            --allow-root

        wp user create $WP_USR $WP_EMAIL --role=author --user_pass=$WP_PWD --allow-root
	wp user meta update 1 show_admin_bar_front false
	wp user meta update 2 show_admin_bar_front false
    else
        echo "WordPress download failed! Retrying..."
        exit 1
    fi
fi

exec php-fpm82
