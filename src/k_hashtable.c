#include "k_hashtable.h"

int 
is_prime(unsigned n) {
    if(n <= 1) {
        return 0;
    }
    if(n <= 3) {
        return 1;
    }
    if(n%2 == 0 || n%3 == 0) {
        return 0;
    }
    int i;
    for(i = 5; i*i <= n; i += 6) {
        if(n%i == 0 || n%(i+2) == 0) {
            return 0;
        }
    }
    return 1;
}

unsigned 
next_prime(unsigned n) {
    while(!is_prime(n)) {
        n++;
    }
    return n;
}

unsigned
hash_function(k_object_t *object, unsigned i, unsigned m) {
    /**
     * For a unique binary object and every i in [0, m-1], 
     * hash_function() must generate a unique permutation 
     * of the set {0, 1, ..., m-1}.
     */
    long long int binary = *(int *)object->data;
    return (*(int *)object->data + i) % m;
}

k_hashtable_t *
hashtable_create() {
    k_hashtable_t *ht = malloc(sizeof(k_hashtable_t));
    ht->max_length = INITIAL_HASHTABLE_SIZE;

    k_object_t *object = (k_object_t *)ht;
    object->data = calloc(ht->max_length, sizeof(k_hashcell_t));
    object->length = 0;
    object->type = K_HASHTABLE;
}

void
hashtable_destroy(k_hashtable_t *ht) {
    free(ht->base.data);
    free(ht);
}

void
hashtable_resize(k_hashtable_t *ht, size_t target) {
    k_object_t *object = (k_object_t *)ht;

    k_hashcell_t *old_cells = (k_hashcell_t *)object->data;
    size_t old_max_length = ht->max_length;

    object->data = calloc(target, sizeof(k_hashcell_t));
    object->length = 0;
    ht->max_length = target;
    assert(object->data);

    int i;
    for(i = 0; i < old_max_length; i++) {
        // Reinsert the old values into the new array
        if(old_cells[i].status & STATUS_FILLED) {
            hashtable_insert(ht, old_cells[i].key, old_cells[i].value);
        }
    }

    free(old_cells);
}

void
hashtable_insert(k_hashtable_t *ht, k_object_t *key, k_object_t *value) {
    k_object_t *object = (k_object_t *)ht;
    k_hashcell_t *cells = (k_hashcell_t *)object->data;

    // Probe for first free cell in the table
    unsigned i, idx;
    for(i = 0; i < ht->max_length; i++) {
        idx = hash_function(key, i, ht->max_length);
        if(!cells[idx].status || (cells[idx].status & STATUS_DELETE)) {
            cells[idx].key = key;
            cells[idx].value = value;
            cells[idx].status = STATUS_FILLED;
            object->length++;
            break;
        }
    }

    // Resize the table if it goes beyond load factor
    if(object->length >= LOAD_FACTOR * ht->max_length) {
        hashtable_resize(ht, next_prime(ht->max_length << 1));
    }
}

void 
hashtable_delete(k_hashtable_t *ht, k_object_t *key) {
    k_object_t *object = (k_object_t *)ht;
    k_hashcell_t *cells = (k_hashcell_t *)object->data;

    unsigned i, idx;
    for(unsigned i = 0; i < ht->max_length; i++) {
        idx = hash_function(key, i, ht->max_length);
        if(!cells[idx].status) {
            return;
        }
        if(cells[idx].key == key && (cells[idx].status & STATUS_FILLED)) {
            cells[idx].status = STATUS_DELETE;
            return;
        }
    }
}

k_object_t *
hashtable_get(k_hashtable_t *ht, k_object_t *key) {
    k_object_t *object = (k_object_t *)ht;
    k_hashcell_t *cells = (k_hashcell_t *)object->data;

    unsigned i, idx;
    for(unsigned i = 0; i < ht->max_length; i++) {
        idx = hash_function(key, i, ht->max_length);
        if(!cells[idx].status) {
            return NULL;
        }
        if(cells[idx].key == key && (cells[idx].status & STATUS_FILLED)) {
            return cells[idx].value;
        }
    }
}