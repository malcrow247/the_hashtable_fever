#ifndef LIST_H
#define LIST_H

#include "common.h"

typedef struct node
{
    int index;
    int value;
    struct node *next;
    struct node *prev;
} node;

typedef struct list
{
    node *head;
    node *tail;
    ull size;
} list;

void create_list(list *lst);
int list_push_back(list *lst, int index, int value);
int list_pop_back(list *lst);
int list_push_front(list *lst, int index, int value);
int list_pop_front(list *lst);
int list_delete_node(list *lst, node *n);
void list_free(list *lst);

#endif // LIST_H
