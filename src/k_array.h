#ifndef K_ARRAY_H_
#define K_ARRAY_H_

#include <assert.h>
#include <string.h>

#include "k_object.h"

#define INIT_ARRAY_SIZE 2

/**
 * A dynamic array implementation
 * that allows the storage of different
 * object types, including itself.
 */
typedef struct {
    k_object_t base;
    size_t max_length;
} k_array_t;

k_array_t *array_create();

void array_destroy(k_array_t *array);

k_object_t *array_get(k_array_t *array, int index);

void array_set(k_array_t *array, k_object_t *object, int index);

void array_append(k_array_t *array, k_object_t *object);

void array_remove(k_array_t *array, int index);

#endif