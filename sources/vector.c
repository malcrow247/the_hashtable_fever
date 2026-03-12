#ifndef VECTOR_C
#define VECTOR_C

#include "vector_list.h"

#include "common.h"

int vector_create(vector_list* v) {
    if (!v) return -1;

    list* data = (list*)calloc(100, sizeof(list));
    if (!data) return -1;

    v->data = data;
    v->size = 100;

    return 0;
}

void vector_free(vector_list* v) {
    if (!v) return;
    if (!v->data) return;

    free(v->data);
}

int vector_resize(vector_list* v, int new_size) {
    if (!v) return -1;

    list* new_data = realloc(v->data, sizeof(list) * new_size);
    if (!new_data) return -1;

    v->data = new_data;

    return 0;
}

#endif  // VECTOR_C
