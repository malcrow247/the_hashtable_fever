#ifndef LIST_C
#define LIST_C

#include "list.h"

int list_create(list* l) {
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;

    return 0;
}

void list_free(list* l) {
    while (l->size > 0) {
        list_pop_front(l);
    }
}

int list_push_back(list* l, int key, int value) {
    if (!l) return 1;
    node* new = malloc(sizeof(node));
    if (!new) return 1;

    new->value = value;
    new->key = key;

    if (l->size == 0) {
        new->prev = NULL;
        l->head = new;
        l->tail = new;
    } else {
        l->tail->next = new;
        new->prev = l->tail;
        l->tail = new;
    }
    l->size++;
    return 0;
}

int list_push_front(list* l, int key, int value) {
    if (!l) return 1;
    node* new = malloc(sizeof(node));
    if (!new) return 1;

    new->value = value;
    new->key = key;

    if (l->size == 0) {
        new->next = NULL;
        l->head = new;
        l->tail = new;
    } else {
        l->head->prev = new;
        new->next = l->head;
        l->head = new;
    }
    l->size++;
    return 0;
}

int list_pop_back(list* l) {
    if (!l) return 1;

    if (l->size == 1) {
        free(l->tail);
        l->head = NULL;
        l->tail = NULL;
        l->size = 0;
    } else if (l->size > 1) {
        l->tail = l->tail->prev;
        free(l->tail->next);
        l->tail->next = NULL;
        l->size--;
    }
    return 0;
}

int list_pop_front(list* l) {
    if (!l) return 1;

    if (l->size == 1) {
        free(l->head);
        l->head = NULL;
        l->tail = NULL;
        l->size = 0;
    } else if (l->size > 0) {
        l->head = l->head->next;
        free(l->head);
        l->head->prev = NULL;
        l->size--;
    }
    return 0;
}

int list_pop(list* l, node* n) {
    if (!l) return -1;
    if (!n) return -1;

    if (l->size == 1) {
        l->size = 0;
        free(n);
        l->head = NULL;
        l->tail = NULL;
    } else if (l->size > 1) {
        if (l->head == n) l->head = n->next;
        if (l->tail == n) l->tail = n->prev;

        n->prev->next = n->next;
        n->next->prev = n->prev;
        free(n);
    }

    return 0;
}

#endif  // LIST_C
