Introduction
===
The `php-bencode` is a PHP extension which can boost the process of encoding and decoding of [Bencode](https://en.wikipedia.org/wiki/Bencode). Supported by [PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP), the project only uses about 1000 lines of codes to implement the basic functions including encoding, decoding, loading, saving and etc.

Installation
===
***Step 1*** Install dependencies
```bash
# Debian, Ubuntu (from launchpad)
apt-get install php5-dev
# Redhat, CentOS, Fedora
yum install php-devel
```
***Step 2*** Install PHP-CPP
```bash
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
cd PHP-CPP
make -j$(nproc)
make install
```
***Step 3*** Build and install
```bash
git clone https://git.tsundere.moe/Frederick888/php-bencode.git
cd php-bencode
make
make install
```

Basic Usage
===
```
php > $dict = BItem::parse("d4:key1l5:hello5:worlde4:key2i99ee");
php > print_r($dict->toMetaArray());
Array
(
    [_type] => BDict
    [_length] => 34
    [_size] => 2
    [_data] => Array
        (
            [key1] => Array
                (
                    [_type] => BList
                    [_length] => 16
                    [_size] => 2
                    [_data] => Array
                        (
                            [0] => Array
                                (
                                    [_type] => BStr
                                    [_length] => 7
                                    [_data] => hello
                                )

                            [1] => Array
                                (
                                    [_type] => BStr
                                    [_length] => 7
                                    [_data] => world
                                )

                        )

                )

            [key2] => Array
                (
                    [_type] => BInt
                    [_length] => 4
                    [_data] => 99
                )

        )

)
php > $dict->set('key2', new BInt(100));
php > echo $dict;
d4:key1l5:hello5:worlde4:key2i100ee
```