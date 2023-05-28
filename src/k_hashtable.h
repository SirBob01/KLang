#ifndef K_HASHTABLE_H_
#define K_HASHTABLE_H_

#include <assert.h>
#include <stdlib.h>

#include "k_object.h"

#define INITIAL_HASHTABLE_SIZE 13
#define STATUS_FILLED          (1 << 0)
#define STATUS_DELETE          (1 << 1)
#define LOAD_FACTOR            0.75

/**
 * A hashtable that maps immutable objects to other
 * kinds of objects using a hashing function. Collisions
 * are handled using open addressing.
 *
 * This is the core data structure behind the
 * garbage collection mark-and-sweep algorithm.
 */
typedef struct {
    k_object_t base;
    size_t max_length;
} k_hashtable_t;

typedef struct {
    k_object_t *key;
    k_object_t *value;
    unsigned char status; // free or filled
} k_hashcell_t;

int is_prime(unsigned n);

unsigned next_prime(unsigned n);

/**
 * This should generate unique values for
 * different types of objects. It uses the direct
 * binary of the data field.
 */
unsigned hash_function(k_object_t *object, unsigned i, unsigned m);

k_hashtable_t *hashtable_create();

void hashtable_destroy(k_hashtable_t *ht);

void hashtable_resize(k_hashtable_t *ht, size_t target);

void hashtable_insert(k_hashtable_t *ht, k_object_t *key, k_object_t *value);

void hashtable_delete(k_hashtable_t *ht, k_object_t *key);

k_object_t *hashtable_get(k_hashtable_t *ht, k_object_t *key);

#endif