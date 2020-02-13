# changelog

v1.2.5

1. Fix memory leak caused by incorrect zval allocation
2. Sort dictionary by keys when encoding (thanks @ttys3 #8)
3. Fix segfault when parsing malformed Bencode integers, e.g. i10 (missing e at the end)
4. Code style (.clang-format, clearer project structure)
5. Various chores (correctly configure valgrind in CI, test against PHP 7.4, etc.)

v1.2.4

1. Catch exceptions and return null in such scenarios (thanks @ttys3 #5)

v1.2.3

1. Simplify source codes
2. Less memory usage

v1.2.2

1. Fix null character handling (thanks @DJATOM #2)
2. Improve tests
3. Update Travis script

v1.2.1

1. Fix pointer abuse
2. Upgrade license


v1.2.0

1. search() method now allows you to search through the Bencode tree
2. Test cases added. Now you can use make test to verify the correctness of your build
3. Bug fixes (segfault, negative number parsing and etc.)


v1.1.0

1. New feature: set_path/get_path/get_path_copy/del_path
2. Fix bug when namespace registration enabled


v1.0.0

1. use zend_register_internal_class_ex to register parent

