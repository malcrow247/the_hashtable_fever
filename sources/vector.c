#ifndef VECTOR_C
#define VECTOR_C

#include "vector.h"

int create_vector(vector *v, unsigned long long size)
{
    if (!v || size == 0)
        return ERR;

    void **a = calloc(size, sizeof(void *));
    if (!a)
        return ERR;

    v->data = a;
    v->size = size;
    v->occupied = 0;

    return OK;
}

void free_vector(vector *v)
{
    if (!v)
        return;

    free(v->data);
}

int vector_resize(vector *v, unsigned long long new_size)
{
    if (!v || new_size == 0 || !v->data)
        return ERR;

    void **a = realloc(v->data, sizeof(void *) * new_size);
    if (!a)
        return ERR;

    v->data = a;
    v->size = new_size;

    if (v->occupied > new_size)
        v->occupied = new_size;

    return OK;
}

int vector_push_back(vector *v, void *element)
{
    if (!v || !v->data)
        return ERR;

    if (v->occupied == v->size)
    {
        int status = vector_resize(v, v->size * 2);
        if (status != OK)
            return ERR;
    }

    v->data[v->occupied] = element;
    v->occupied++;

    return OK;
}

void *vector_get_element(vector *v, unsigned long long index)
{
    if (!v || !v->data || index >= v->occupied)
        return NULL;

    return v->data[index];
}

#endif // VECTOR_C