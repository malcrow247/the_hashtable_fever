#ifndef LIST_C
#define LIST_C

#include "list.h"

void create_list(list *lst)
{
    if (!lst)
        return;

    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;
}

int list_push_back(list *lst, int index, int value)
{
    if (!lst)
        return ERR;

    node *new = malloc(sizeof(node));

    if (!new)
        return ERR;

    new->index = index;
    new->value = value;
    new->next = NULL;
    new->prev = lst->tail;

    if (lst->size == 0)
        lst->head = new;
    else
        lst->tail->next = new;
    lst->tail = new;

    lst->size++;

    return OK;
}

int list_pop_back(list *lst)
{
    if (!lst)
        return ERR;

    if (lst->size > 1)
    {
        lst->tail = lst->tail->prev;
        free(lst->tail->next);
        lst->tail->next = NULL;
        lst->size--;
    }
    else if (lst->size == 1)
    {
        free(lst->tail);
        lst->head = NULL;
        lst->tail = NULL;
        lst->size = 0;
    }

    return OK;
}

int list_push_front(list *lst, int index, int value)
{
    if (!lst)
        return ERR;

    node *new = malloc(sizeof(node));

    if (!new)
        return ERR;

    new->index = index;
    new->value = value;
    new->prev = NULL;
    new->next = lst->head;

    if (lst->size == 0)
        lst->tail = new;
    else
        lst->head->prev = new;
    lst->head = new;

    lst->size++;

    return OK;
}

int list_pop_front(list *lst)
{
    if (!lst || lst->size == 0)
        return ERR;

    if (lst->size > 1)
    {
        lst->head = lst->head->next;
        free(lst->head->prev);
        lst->head->prev = NULL;
        lst->size--;
    }
    else if (lst->size == 1)
    {
        free(lst->head);
        lst->head = NULL;
        lst->tail = NULL;
        lst->size = 0;
    }

    return OK;
}

int list_delete_node(list *lst, node *n)
{
    if (!lst || !n)
        return ERR;

    if (n->prev != NULL)
    {
        n->prev->next = n->next;
    }
    else
    {
        lst->head = NULL;
    }

    if (n->next != NULL)
    {
        n->next->prev = n->prev;
    }
    else
    {
        lst->tail = NULL;
    }

    free(n);

    return OK;
}

void list_free(list *lst)
{
    if (!lst)
        return;

    while (lst->size > 0)
        list_pop_back(lst);
}

#endif // LIST_C
