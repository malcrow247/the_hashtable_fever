#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "common.h"
#include "list.h"
#include "vector.h"

#define HASHTABLE_START_SIZE 10000

typedef struct hashtable
{
    vector data;
    ull size;
    ull hash_mult;
    ull hash_plus;
} hashtable;

int hashtable_create(hashtable *h);
void hashtable_free(hashtable *h);
int hashtable_resize(hashtable *h, ull new_size);
int hashtable_set_value(hashtable *h, int index, int value);
int hashtable_get_value(hashtable *h, int index, int *result);
int hashtable_delete(hashtable *h, int index);

#endif // HASHTABLE_H
