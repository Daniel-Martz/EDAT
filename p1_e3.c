#include "graph.h"
#include "vertex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f = NULL;
    Graph *g = NULL;

    if (!(f = fopen("g1.txt", "r")))
    {
        printf("Hubo un error");
        return 1;
    }

    g = graph_init();
    if (!g)
    {
        printf("Hubo un error");
        fclose(f);
        return 1;
    }

    if (graph_readFromFile(f, g) == ERROR)
    {
        printf("Hubo un error");
        graph_free(g);
        fclose(f);
        return 0;
    }

    if (graph_print(stdout, g) == -1)
    {
        printf("Hubo un error");
    }

    graph_free(g);
    fclose(f);

    return 0;
}