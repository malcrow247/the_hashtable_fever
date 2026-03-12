#ifndef LIST_H
#define LIST_H

#include "common.h"

typedef struct node{
    struct node *next;
    struct node *prev;    
    int key;
    int value;
} node;

typedef struct list{
    node *head;
    node *tail;
    ull size;
} list;

int list_create(list *l);
void list_free(list *l);
int list_push_back(list *l, int key, int value);
int list_pop_back(list *l);
int list_push_front(list *l, int key, int value);
int list_pop_front(list *l);
int list_pop(list *l, node *n);

#endif // LIST_H
