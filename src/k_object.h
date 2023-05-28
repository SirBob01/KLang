#ifndef K_OBJECT_H_
#define K_OBJECT_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * Define the atomic data types.
 * More complex data structures can be
 * built on top of this.
 */
typedef enum {
    K_INTEGER,
    K_FLOAT,
    K_BOOL,
    K_STRING,
    K_ARRAY,
    K_HASHTABLE
} KObjectType;

/**
 * Every atomic datatype can be expressed
 * as a k_object_t pointer by converting it.
 * This includes variable length types like
 * arrays and hashtables.
 */
typedef struct {
    void *data;
    size_t length;
    KObjectType type;
} k_object_t;

k_object_t *object_create(void *data, size_t length, KObjectType type);

void object_destroy(k_object_t *object);

k_object_t *object_clone(k_object_t *parent);

unsigned object_id(k_object_t *object);

#endif