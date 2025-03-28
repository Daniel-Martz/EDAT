
#include "stack.h"
#include "file_utils.h"
#include "vertex.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout, P_stack_ele_cmp comparar)
{
    void *e = NULL;
    Stack *ps = NULL;

    if (!sin1 || !sin2 || !sout)
    {
        return ERROR;
    }

    while (stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE)
    {
        if (comparar(stack_top(sin1), stack_top(sin2)) > 0)
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
    int i;
    long vertex_size;
    char str_aux[MAX_SIZE];
    Vertex *vertex_aux = NULL;

    if (stack == NULL)
    {
        return ERROR;
    }

    if ((f = fopen(filename, "r")) == NULL)
    {
        return ERROR;
    }

    fscanf(f, "%ld", &vertex_size);

    fgets(str_aux, MAX_SIZE, f); /* Leera un \n destras del numero*/

    for (i = 0; i < vertex_size; i++)
    {

        fgets(str_aux, MAX_SIZE, f);
        if ((vertex_aux = vertex_initFromString(str_aux)) == NULL)
        {
            fclose(f);
            return ERROR;
        }

        if (stack_push(stack, vertex_aux) == ERROR)
        {
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
        vertex_free(e);
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
    stack_print(stdout, s1, vertex_print);
    fprintf(stdout, "\nRanking 1\n");
    stack_print(stdout, s2, vertex_print);

    mergeStacks(s1, s2, sout, vertex_cmp);

    fprintf(stdout, "\nJoint Ranking\n");
    stack_print(stdout, sout, vertex_print);

    free_stack_elements(sout);

    stack_free(s1);
    stack_free(s2);
    stack_free(sout);
    return 0;
}
