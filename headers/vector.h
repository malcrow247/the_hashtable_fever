#ifndef VECTOR_H
#define VECTOR_H

#include "common.h"

typedef struct vector
{
    unsigned long long size;
    unsigned long long occupied;
    void **data;
} vector;

int create_vector(vector *v, unsigned long long size);
void free_vector(vector *v);
int vector_resize(vector *v, unsigned long long new_size);
int vector_push_back(vector *v, void *element);
void *vector_get_element(vector *v, unsigned long long index);

#endif // VECTOR_H