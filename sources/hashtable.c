#ifndef HASHTABLE_C
#define HASHTABLE_C

#include "hashtable.h"

int hashtable_create(hashtable *h)
{
    if (!h)
        return ERR;

    int status = create_vector(&(h->data), HASHTABLE_START_SIZE);

    if (status != OK)
        return status;

    for (ull i = 0; i < HASHTABLE_START_SIZE; ++i)
    {
        list *lst = malloc(sizeof(list));

        if (!lst)
        {
            for (ull j = 0; j < i; ++j)
            {
                list_free((list *)h->data.data[j]);
                free(h->data.data[j]);
            }
            free(h->data.data);
            return ERR;
        }

        create_list(lst);
        h->data.data[i] = lst;
    }

    h->size = 0;

    while ((h->hash_mult = rand()) == 0)
    {
    }

    while ((h->hash_plus = rand()) == 0)
    {
    }

    return OK;
}

void hashtable_free(hashtable *h)
{
    if (!h || !h->data.data)
        return;

    for (ull i = 0; i < h->data.size; ++i)
    {
        list_free((list *)h->data.data[i]);
        free(h->data.data[i]);
    }

    free(h->data.data);
}

int hashtable_resize(hashtable *h, ull new_size)
{
    if (!h)
        return ERR;

    void **new_data = calloc(new_size, sizeof(void *));

    for (ull i = 0; i < new_size; ++i)
    {
        list *new_lst = malloc(sizeof(list));

        if (!new_lst)
        {
            for (ull j = 0; j < i; ++j)
            {
                list_free((list *)new_data[j]);
                free(new_data[j]);
            }

            free(new_data);

            return ERR;
        }

        create_list(new_lst);
        new_data[i] = new_lst;
    }

    for (ull i = 0; i < h->data.size; ++i)
    {
        node *now = ((list *)h->data.data[i])->head;
        while (now != NULL)
        {
            int index = now->index, value = now->value;
            ull hashtable_index =
                (((ull)index) * h->hash_mult + h->hash_plus) % new_size;

            int status = list_push_back((list *)new_data[hashtable_index], index, value);

            if (status != OK)
            {
                for (ull j = 0; j < new_size; ++j)
                {
                    list_free((list *)new_data[j]);
                    free(new_data[j]);
                }

                free(new_data);
                return ERR;
            }
        }

        list_free((list *)h->data.data[i]);
        free(h->data.data[i]);
    }

    free(h->data.data);

    h->data.data = new_data;
    h->data.size = new_size;

    return OK;
}

int hashtable_set_value(hashtable *h, int index, int value)
{
    if (!h)
        return ERR;

    ull hashtable_index = (((ull)index) * h->hash_mult + h->hash_plus);

    node *n = ((list *)h->data.data[hashtable_index % h->data.size])->head;
    while (n != NULL && n->index != index)
        n = n->next;

    if (n != NULL)
    {
        n->value = value;
        return OK;
    }

    if ((float)h->size / (float)h->data.size >= 0.7)
        if (hashtable_resize(h, h->data.size * 2) != OK)
            return ERR;

    if (list_push_back(h->data.data[hashtable_index % h->data.size], index, value) != OK)
        return ERR;

    h->size++;
    return OK;
}

int hashtable_get_value(hashtable *h, int index, int *result)
{
    ull hashtable_index =
        (((ull)index) * h->hash_mult + h->hash_plus) % h->data.size;

    node *now = ((list *)h->data.data[hashtable_index])->head;

    while (now != NULL && now->index != index)
        now = now->next;

    if (now != NULL)
    {
        *result = now->value;
        return OK;
    }
    return NOTEXISTS;
}

int hashtable_delete(hashtable *h, int index)
{
    if (!h || !h->data.data)
        return ERR;

    ull hashtable_index =
        (((ull)index) * h->hash_mult + h->hash_plus) % h->data.size;

    list *lst = (list *)h->data.data[hashtable_index];

    node *now = lst->head;
    while (now != NULL && now->index != index)
        now = now->next;

    if (now == NULL)
        return NOTEXISTS;

    int status = list_delete_node(lst, now);

    if (status != OK)
        return ERR;

    h->size--;

    return OK;
}

#endif // HASHTABLE_C
