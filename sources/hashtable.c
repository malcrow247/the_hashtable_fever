#ifndef HASHTABLE_C
#define HASHTABLE_C

#include "hashtable.h"

int hashtable_create(hashtable* h) {
    if (!h) return -1;

    h->k = rand() % (int)1e7;
    h->b = rand() % (int)1e7;

    h->size = 0;

    int status = vector_create(&(h->data));
    return status;
}

void hashtable_free(hashtable* h) {
    if (!h) return;

    vector_free(&(h->data));
}

int hashtable_set(hashtable* h, int key, int value) {
    if (!h) return -1;

    int status;

    // hash(x) = k * x + b
    int hash = (h->k * key + h->b) % h->data.size;

    int isfound = 0;
    node* now = h->data.data[hash].head;

    while (now != NULL) {
        if (now->key == key) {
            isfound = 1;
            break;
        }

        now = (node*)now->next;
    }

    if (isfound) {
        now->value = value;
        return 0;
    } else {
        status = list_push_back(&(h->data.data[hash]), key, value);
        return status;
    }
}

int hashtable_delete(hashtable* h, int key) {
    if (!h) return -1;

    int hash = (h->k * key + h->b) % h->data.size;

    int isfound = 0;
    node* now = h->data.data[hash].head;

    while (now != NULL) {
        if (now->key == key) {
            isfound = 1;
            break;
        }

        now = (node*)now->next;
    }

    if (isfound) {
        int status = list_pop(&(h->data.data[hash]), now);

        return status;
    }

    return 0;
}

int hashtable_search(hashtable* h, int key, int* return_value) {
    if (!h) return -1;

    int hash = (h->k * key + h->b) % h->data.size;

    node* now = h->data.data[hash].head;

    while (now != NULL && now->key != key) {
        now = (node*)now->next;
    }

    if (now != NULL) {
        *return_value = now->value;
        return 0;
    }

    return -1;
}

#endif  // HASHTABLE_C
