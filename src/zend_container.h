#ifndef BENCODE_HEADER_ZEND_CONTAINER
#define BENCODE_HEADER_ZEND_CONTAINER

extern "C" {
#include "php.h"

// https://github.com/mongodb/mongo-php-driver/commit/d785d5e15e826f20b73c804e5ad3c8fb351f6a06

#if PHP_VERSION_ID >= 80000
#define BENCODE_COMPAT_OBJ_P(val) Z_OBJ_P(val)
#define BENCODE_VAL zend_object
#define BENCODE_COMPAT_GET_OBJ(val) val
#else /* PHP_VERSION_ID < 80000 */
#define BENCODE_COMPAT_OBJ_P(val) val
#define BENCODE_VAL zval
#define BENCODE_COMPAT_GET_OBJ(val) Z_OBJ_P(val)
#endif /* PHP_VERSION_ID >= 80000 */

// c func borrowed from https://github.com/php/php-src/blob/e08ce4c13db6e9aecd3497cd270b72d06c649bc7/ext/standard/array.c#L245
/*
 * https://github.com/php/php-src/blob/898bb97706326311a367aaef35b3f95510100f3c/UPGRADING.INTERNALS#L113
 * The zend_hash_sort and zend_hash_minmax APIs now accept a comparison
     function with the following signature:

         typedef int (*bucket_compare_func_t)(Bucket *a, Bucket *b);

     Previously compare_func_t was used, which accepted void pointers.
     Furthermore, the return type of zend_hash_sort and zend_ts_hash_sort has
     been changed from int to void; these functions always succeed.
 */
#if PHP_VERSION_ID >= 80000
static int php_array_key_compare_string(Bucket *a, Bucket *b)
#else /* PHP_VERSION_ID < 80000 */
static int php_array_key_compare_string(const void *a, const void *b)
#endif /* PHP_VERSION_ID >= 80000 */
{
    Bucket *f = (Bucket *)a;
    Bucket *s = (Bucket *)b;
    const char *s1, *s2;
    size_t l1, l2;
    char buf1[MAX_LENGTH_OF_LONG + 1];
    char buf2[MAX_LENGTH_OF_LONG + 1];

    if (f->key) {
        s1 = f->key->val;
        l1 = f->key->len;
    } else {
        s1 = zend_print_long_to_buf(buf1 + sizeof(buf1) - 1, f->h);
        l1 = buf1 + sizeof(buf1) - 1 - s1;
    }
    if (s->key) {
        s2 = s->key->val;
        l2 = s->key->len;
    } else {
        s2 = zend_print_long_to_buf(buf2 + sizeof(buf2) - 1, s->h);
        l2 = buf2 + sizeof(buf2) - 1 - s2;
    }
    return zend_binary_strcmp(s1, l1, s2, l2);
}
}

#include "bdict.h"
#include "bint.h"
#include "bitem.h"
#include "blist.h"
#include "bstr.h"

/* clang-format off */
#define BENCODE_ERROR_BITEM             1
#define BENCODE_ERROR_INVALID_ARGUMENT  2
#define BENCODE_ERROR_OUT_OF_RANGE      3
#define BENCODE_ERROR_UNDEFINED         4
#define BENCODE_ERROR_UNKNOWN           5
/* clang-format on */

#define ZEND_CONTAINER_PRE(bclass) \
    typedef struct {               \
        bclass *bnode_data;        \
        zend_object std;           \
    } bclass##_object;

ZEND_CONTAINER_PRE(bitem)
ZEND_CONTAINER_PRE(bdict)
ZEND_CONTAINER_PRE(blist)
ZEND_CONTAINER_PRE(bstr)
ZEND_CONTAINER_PRE(bint)

#define ZEND_CONTAINER_INIT(bclass)                                  \
    static zend_object_handlers bclass##_object_handlers;            \
    static zend_class_entry *bclass##_ce;                            \
    static bclass##_object *bclass##_fetch_object(zend_object *obj); \
    static void bclass##_free_storage(zend_object *object);          \
    static zend_object *bclass##_object_clone(BENCODE_VAL *object);  \
    static zend_object *bclass##_object_new(zend_class_entry *ce);

class zend_container
{
public:
    ZEND_CONTAINER_INIT(bitem)
    ZEND_CONTAINER_INIT(bdict)
    ZEND_CONTAINER_INIT(blist)
    ZEND_CONTAINER_INIT(bstr)
    ZEND_CONTAINER_INIT(bint)
    static std::string bnode_object_get_class_name(zval *object)
    {
        zend_bool ini_ns = zend_ini_long((char *)"bencode.namespace", 17, 0);
        std::string class_name(ZSTR_VAL(Z_OBJ_P(object)->ce->name));
        if (ini_ns) {
            return class_name.substr(8);
        } else {
            return class_name;
        }
    }
    static zend_object *bnode_object_clone(zval *object)
    {
        zval new_object;
        ZVAL_OBJ(&new_object, Z_OBJ_P(object)->handlers->clone_obj(BENCODE_COMPAT_OBJ_P(object)));
        return Z_OBJ(new_object);
    }
    static inline bitem *bnode_fetch_object_data(zend_object *obj)
    {
        return (bitem *)(*((uintptr_t *)((char *)obj - sizeof(uintptr_t))));
    }
};

#endif
