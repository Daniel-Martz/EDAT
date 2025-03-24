#include "graph.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

int main(int argc, char**argv)
{
    Graph *g = NULL;
    char filename[MAX_SIZE];
    long from, to;
    FILE *f=NULL;
    if (argc < 4)
    {
        fprintf(stderr, "Debe introducir: %s  <.txt> <Id origen> <Id llegada>", argv[0]);
        return -1;
    }

    strcpy(filename, argv[1]);
    from = atoi(argv[2]);
    to = atoi(argv[3]);

    g = graph_init();
    if (g == NULL)
    {
        return -1;
    }

    if (!(f=fopen(filename, "r")))
    {
        graph_free(g);
        return -1;
    }

    graph_readFromFile(f, g);

    printf("Input grahp:\n");
    graph_print(stdout, g);

    printf("From Vrtex id: %ld\n", from);
    printf("To Vertex id: %ld\n", to);
    printf ("Output\n");
    graph_depthSearch(g, from, to);
    
    graph_free(g);
    fclose(f);
    return 0;
}
