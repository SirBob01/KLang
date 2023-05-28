#include "k_object.h"
#include "k_array.h"

k_object_t *object_create(void *data, size_t length, KObjectType type) {
    k_object_t *object = malloc(sizeof(k_object_t));
    assert(object);

    object->data = malloc(length);
    assert(object->data);

    object->length = length;
    object->type = type;
    memcpy(object->data, data, length);

    return object;
}

void object_destroy(k_object_t *object) {
    free(object->data);
    free(object);
}

k_object_t *object_clone(k_object_t *parent) {
    return object_create(parent->data, parent->length, parent->type);
}

unsigned object_id(k_object_t *object) { return (uintptr_t)object; }