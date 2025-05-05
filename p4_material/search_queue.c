#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "bstree.h"
#include "search_queue.h"

struct _SearchQueue
{
    BSTree *data;
};

SearchQueue *search_queue_new(P_ele_print print_ele, P_ele_cmp cmp_ele)
{
    SearchQueue *s = NULL;

    if (print_ele == NULL || cmp_ele == NULL)
    {
        return NULL;
    }

    s = malloc(sizeof(SearchQueue));
    if (!s)
    {
        return NULL;
    }

    s->data = tree_init(print_ele, cmp_ele);
    if (s->data == NULL)
    {
        free(s);
        return NULL;
    }
    return s;
}

void search_queue_free(SearchQueue *q)
{
    if (q == NULL)
    {
        return;
    }
    tree_destroy(q->data);
    free(q);
    return;
}

Bool search_queue_isEmpty(const SearchQueue *q)
{
    if (q == NULL || q->data == NULL)
    {
        return TRUE;
    }

    return tree_isEmpty(q->data);
}

Status search_queue_push(SearchQueue *q, void *ele)
{
    if (q == NULL || ele == NULL)
    {
        return ERROR;
    }
    return tree_insert(q->data, ele);
}

void *search_queue_pop(SearchQueue *q)
{
    void *e = NULL;
    if (q == NULL || q->data == NULL)
    {
        return NULL;
    }
    if(tree_isEmpty(q->data) == TRUE){
        return NULL;
    }

    e = tree_find_min(q->data);
    if (e != NULL)
    {
        tree_remove(q->data, e);
    }
    return e;
}

void *search_queue_getFront(const SearchQueue *q)
{
    if (q == NULL || q->data == NULL)
    {
        return NULL;
    }
    return tree_find_min(q->data);
}

void *search_queue_getBack(const SearchQueue *q)
{
    if (q == NULL || q->data == NULL)
    {
        return NULL;
    }

    return tree_find_max(q->data);
}

size_t search_queue_size(const SearchQueue *q)
{
    if (q == NULL || q->data == NULL)
    {
        return 0;
    }

    return tree_size(q->data);
}

int search_queue_print(FILE *fp, const SearchQueue *q)
{
    if (fp == NULL || q == NULL || q->data == NULL)
    {
        return -1;
    }
    return tree_inOrder(fp, q->data);
}

void *search_queue_popBack(SearchQueue *q)
{
    void *e = NULL;
    if (q == NULL || q->data == NULL)
    {
        return NULL;
    }
    if(tree_isEmpty(q->data) == TRUE){
        return NULL;
    }

    e = tree_find_max(q->data);
    if (e != NULL)
    {
        tree_remove(q->data, e);
    }
    return e;
}

void search_queue_free_and_elements(SearchQueue *q)
{
    if (q == NULL)
    {
        return;
    }
    tree_destroy_and_elements(q->data);
    free(q);
    return;
}