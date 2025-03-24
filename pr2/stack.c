#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 2 /* init stack capacity*/
#define FCT_CAPACITY 2  /* multiply the stack capacity*/

struct _Stack
{
    void **item;  /*!<Static array of elements*/
    int top;      /*!<index of the top element in the stack*/
    int capacity; /*!<xcapacity of the stack*/
};


Stack *stack_init()
{
    Stack *s = NULL;
    int i = 0;

    if (!(s = (Stack *)calloc(1, sizeof(Stack))))
    {
        return NULL;
    }

    if (!(s->item = (void **)calloc(INIT_CAPACITY, sizeof(void *))))
    {
        free(s);
        return NULL;
    }
    for (i = 0; i < INIT_CAPACITY; i++)
    {
        s->item[i] = NULL;
    }
    s->top = -1;
    s->capacity = INIT_CAPACITY;

    return s;
}

void stack_free(Stack *s)
{
    int i;
    if (s == NULL)
    {
        return;
    }
    for (i = 0; i < s->capacity; i++)
    {
        free(s->item[i]);
    }
    free(s->item);
    free(s);
}


Status stack_push(Stack *s, const void *ele)
{
    if (s == NULL || ele == NULL)
    {
        return ERROR;
    }

    if (s->top == s->capacity)
    {
        if (!(s->item = realloc(s->item, FCT_CAPACITY * s->capacity * sizeof(void *))))
        {
            return ERROR;
        }
        s->capacity = s->capacity * FCT_CAPACITY;
    }
    s->item[s->top] = (void *)ele;
    s->top++;
    return OK;
}


void *stack_pop(Stack *s)
{
    void *e = NULL;
    if (!s)
        return NULL;

    e = s->item[s->top];
    s->item[s->top] = NULL;
    s->top--;
    return (void *)e;
}

void *stack_top(const Stack *s)
{
    if (!s)
        return NULL;

    return (void *)s->item[s->top];
}

Bool stack_isEmpty(const Stack *s)
{
    if (!s)
    {
        return TRUE;
    }
    if (s->top == -1)
        return TRUE;

    return FALSE;
}

size_t stack_size(const Stack *s)
{
    if (s == NULL)
    {
        return -1;
    }
    return s->top + 1;
}


int stack_print(FILE *fp, const Stack *s, P_stack_ele_print f)
{
    int i, total = 0;
    if (fp == NULL || f == NULL || s == NULL)
    {
        return -1;
    }

    for (i = 0; i <= s->top; i++)
    {
        total = f(fp, s->item[i]);
    }
    return total;
}

