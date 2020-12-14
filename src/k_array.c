#include "k_array.h"

k_array_t *
array_create() {
    k_array_t *arr = malloc(sizeof(k_array_t));
    arr->max_length = INIT_ARRAY_SIZE;

    k_object_t *object = (k_object_t *)arr;
    object->data = malloc(sizeof(k_object_t *) * arr->max_length);
    assert(object->data);

    object->length = 0;
    object->type = K_ARRAY;
    return arr;
}

void
array_destroy(k_array_t *arr) {
    free(arr->base.data);
    free(arr);
}

k_object_t *
array_get(k_array_t *array, int index) {
    k_object_t *base = (k_object_t *)array;
    assert(base->length > 0);

    k_object_t **memline = (k_object_t **)base->data;
    return memline[index];
}

void
array_set(k_array_t *array, k_object_t *object, int index) {
    k_object_t *base = (k_object_t *)array;
    assert(index < base->length && index >= 0);

    k_object_t **memline = (k_object_t **)base->data;
    k_object_t *prev = memline[index];
    
    memline[index] = object;
}

void 
array_append(k_array_t *array, k_object_t *object) {
    k_object_t *base = (k_object_t *)array;
    if(base->length + 1 == array->max_length) {
        array->max_length <<= 1;
        base->data = realloc(
            base->data, 
            sizeof(k_object_t *) * array->max_length
        );
        assert(base->data);
    }

    size_t offset = (base->length++) * sizeof(k_object_t *);
    memcpy(base->data + offset, &object, sizeof(k_object_t *));
}

void
array_remove(k_array_t *array, int index) {
    k_object_t *base = (k_object_t *)array;
    assert(base->length > 0);

    k_object_t **memline = (k_object_t **)base->data;

    k_object_t *target = memline[index];
    
    int i = 0;
    for(i = index+1; i < base->length; i++) {
        memline[i-1] = memline[i];
    }
    base->length--;
}