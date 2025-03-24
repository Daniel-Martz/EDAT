#include "types.h"
#include "stack.h"
#include "file_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM 30
#define MAX_SIZE 100
/**
 * @brief: Merges two stacks
 *
 * @param sin1, first input stack
 * @param sin2, second input stack
 * @param sout, result stack
 * @return The function returns OK or ERROR
 **/

/* Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout)
{
    void *e;
    Stack *ps;

    if (!sin1 || !sin2 || !sout)
    {
        return ERROR;
    }

    while (stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE)
    {
        if (*(float *)stack_top(sin1) > *(float *)stack_top(sin2))
        {
            e = stack_top(sin1);
        }
        else
        {
            e = stack_pop(sin2);
        }
        stack_push(sout, e);
    }

    if (stack_isEmpty(sin1) == TRUE)
    {
        ps = sin2;
    }
    else
    {
        ps = sin1;
    }

    while (stack_isEmpty(ps) == FALSE)
    {
        e = stack_pop(ps);
        stack_push(sout, e);
    }

    return OK;
}
*/

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout, P_stack_ele_cmp f)
{
    void *e;
    Stack *ps;

    if (!sin1 || !sin2 || !sout)
    {
        return ERROR;
    }

    while (stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE)
    {
        if (f(stack_top(sin1), stack_top(sin2)) > 0)
        {
            e = stack_pop(sin1);
        }
        else
        {
            e = stack_pop(sin2);
        }
        stack_push(sout, e);
    }

    if (stack_isEmpty(sin1) == TRUE)
    {
        ps = sin2;
    }
    else
    {
        ps = sin1;
    }

    while (stack_isEmpty(ps) == FALSE)
    {
        e = stack_pop(ps);
        stack_push(sout, e);
    }

    return OK;
}

Status read_from_file(Stack *stack, char *filename)
{
    FILE *f = NULL;
    float *aux2 = NULL;
    float aux = 0;
    int i = 0;
    long stack_size;

    if (stack == NULL)
    {
        return ERROR;
    }

    if ((f = fopen(filename, "r")) == NULL)
    {
        return ERROR;
    }

    fscanf(f, "%ld", &stack_size);

    for (i = 0; i < stack_size; i++)
    {
        if (fscanf(f, "%f", &aux) != 1)
        {
            fclose(f);
            return ERROR;
        }
        aux2 = float_init(aux);
        if (stack_push(stack, aux2) == ERROR)
        {
            free(aux2);
            fclose(f);
            return ERROR;
        }
    }

    fclose(f);
    return OK;
}

void free_stack_elements(Stack *stack)
{
    void *e;
    if (!stack)
        return;

    while (!stack_isEmpty(stack))
    {
        e = stack_pop(stack);
        free(e);
    }
}

int main(int argc, char **argv)
{
    Stack *s1 = NULL, *s2 = NULL, *sout = NULL;
    char filename_1[MAX_SIZE], filename_2[MAX_SIZE];

    if (argc < 3)
    {
        fprintf(stderr, "Debe introducir: %s <archivo_1> <archivo 2>", argv[0]);
        return -1;
    }

    if (!(s1 = stack_init()))
    {
        return -1;
    }
    if (!(s2 = stack_init()))
    {
        stack_free(s1);
        return -1;
    }
    if (!(sout = stack_init()))
    {
        stack_free(s1);
        stack_free(s2);
        return -1;
    }

    strcpy(filename_1, argv[1]);
    strcpy(filename_2, argv[2]);

    read_from_file(s1, filename_1);
    read_from_file(s2, filename_2);

    fprintf(stdout, "\nRanking 0\n");
    stack_print(stdout, s1, float_print);
    fprintf(stdout, "\nRanking 1\n");
    stack_print(stdout, s2, float_print);

    mergeStacks(s1, s2, sout, float_cmp);

    fprintf(stdout, "\nJoint Ranking\n");
    stack_print(stdout, sout, float_print);

    free_stack_elements(sout);

    stack_free(s1);
    stack_free(s2);
    stack_free(sout);
    return 0;
}