#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "common.h"
#include "list.h"
#include "vector_list.h"

// hash(x) = k * x + b
typedef struct hashtable {
    vector_list data;  // вектор списков
    ull size;  // количество элементов в хеш-таблице
    int k;
    int b;
} hashtable;

int hashtable_create(hashtable* h);
void hashtable_free(hashtable* h);

int hashtable_set(hashtable* h, int key, int value);
int hashtable_delete(hashtable* h, int key);

int hashtable_search(hashtable* h, int key, int* return_value);

#endif  // HASHTABLE_H
