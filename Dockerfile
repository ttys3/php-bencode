ARG PHP_VER_TAG=8.0.0-fpm-buster
FROM php:${PHP_VER_TAG}

ENV IMAGE_NAME=php-ext-bencode \
TZ="Asia/Shanghai"

# docker-php-ext-install -j$(nproc) /tmp/bencode; \

COPY . /tmp/bencode

WORKDIR /tmp/bencode

RUN set -eux; \
        \
        echo "current architecture is: $(dpkg --print-architecture)"; \
        ln -sf /usr/share/zoneinfo/${TZ} /etc/localtime; \
        echo "${TZ}" >  /etc/timezone; \
        sed -i 's|http://deb.debian.org|https://mirrors.ustc.edu.cn|g' /etc/apt/sources.list; \
        sed -i 's|http://security.debian.org|https://mirrors.ustc.edu.cn|g' /etc/apt/sources.list; \
        apt-get update; \
        apt-get install -y --no-install-recommends libstdc++-8-dev; \
        docker-php-ext-configure /tmp/bencode; \
        docker-php-ext-install -j1 /tmp/bencode; \
        docker-php-ext-enable bencode; \
        ls -lhp /usr/local/etc/php/conf.d; \
        rm -rf /tmp/bencode; \
        rm -rf /tmp/*; \
        rm -rf /var/cache/apk/*; \
        rm -rf /usr/share/gtk-doc; \
        ls -lhpR /usr/local/lib/php/extensions/; \
        mkdir -p /build/usr/local/lib/php/extensions/no-debug-non-zts-20200930/; \
        mkdir -p /build/usr/local/etc/php/conf.d/; \
        echo "bencode.namespace=1" >> /usr/local/etc/php/conf.d/docker-php-ext-bencode.ini; \
        cp -v /usr/local/lib/php/extensions/no-debug-non-zts-20200930/bencode.so /build/usr/local/lib/php/extensions/no-debug-non-zts-20200930/bencode.so; \
        cp -v /usr/local/etc/php/conf.d/docker-php-ext-bencode.ini /build/usr/local/etc/php/conf.d/; \
        echo "PHP bencode module enabled: " && php-fpm -m | grep bencode; \
        echo 'test: '; \
        php -r 'print_r(\bencode\bitem::parse("d4:infod6:lengthi364e4:name8:test.rare3:inti1548400939e4:listl5:UTF-83:GBKe6:string13:uTorrent/3130e")->to_array());'; \
        echo "container date: " && date; \
        echo "build successfully"
