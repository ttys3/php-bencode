#CMakeLists.txt for PHP-extension

cmake_minimum_required(VERSION 3.15)
set(PHP_EXT_NAME bencode)
project(${PHP_EXT_NAME})

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src)

#Stop CMake from prepending `lib` to php extension
set(CMAKE_SHARED_LIBRARY_PREFIX "")
#set_target_properties(bencode PROPERTIES PREFIX "")

set(PHP_SRC_PATH /opt/remi/php80/root/usr/include/php)
include_directories(
        "${PHP_SRC_PATH}"
        "${PHP_SRC_PATH}/main"
        "${PHP_SRC_PATH}/Zend"
        "${PHP_SRC_PATH}/TSRM"
        "${PHP_SRC_PATH}/ext"
        "${PHP_SRC_PATH}/sapi")


add_library(${PHP_EXT_NAME} SHARED
        src/bdict.cc
        src/bdict.h
        src/bencode.cc
        src/binit.h
        src/bint.cc
        src/bint.h
        src/bitem.cc
        src/bitem.h
        src/blist.cc
        src/blist.h
        src/bstr.cc
        src/bstr.h
        src/zend_container.h
        php_bencode.h)

message(STATUS "End cmaking of PHP extension ${PHP_EXT_NAME}")