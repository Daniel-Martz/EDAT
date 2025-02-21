#include "graph.h"
#include "vertex.h"
#include <stdio.h>

int main()
{
    Graph *g = NULL;
    int i;
    long *arrar_aux = NULL;
    /*creation of auxiliars constants*/
    long id1 = 111, id2 = 222;
    char tag1[] = "Madrid", tag2[] = "Toledo";
    
    g = graph_init();

    printf("Inserting %s... result...: ", tag1);
    if (graph_newVertex(g, "id:111 tag:Madrid state:0") == OK)
    {
        printf("1");
    }
    else
    {
        printf("ERROR");
    }
    printf("\n");

    printf("Inserting %s... result...: ", tag2);
    if (graph_newVertex(g, "id:222 tag:Toledo state:0") == OK)
    {
        printf("1");
    }
    else
    {
        printf("ERROR");
    }
    printf("\n");

    printf("Inserting edge: %ld --> %ld", id2, id1);
    if (graph_newEdge(g, id2, id1) == ERROR)
    {
        printf("ERROR");
        graph_free(g);
        return 0;
    }
    printf("\n");

    printf("%ld --> %ld? ", id1, id2);
    if (graph_connectionExists(g, id1, id2) == FALSE)
    {
        printf("NO");
    }
    else
    {
        printf("YES");
    }
    printf("\n");

    printf("%ld --> %ld? ", id2, id1);
    if (graph_connectionExists(g, id2, id1) == FALSE)
    {
        printf("NO");
    }
    else
    {
        printf("YES");
    }
    printf("\n");

    printf("Number of connections from %ld: ", id1);
    printf("%d", graph_getNumberOfConnectionsFromId(g, id1));
    printf("\n");

    printf("Number of connections from %s: ", tag2);
    printf("%d", graph_getNumberOfConnectionsFromTag(g, tag2));
    printf("\n");

    printf("Connections from %s: ", tag2);
    arrar_aux = graph_getConnectionsFromTag(g, tag2);
    if (arrar_aux != NULL)
    {
        for (i = 0; i < graph_getNumberOfConnectionsFromTag(g, tag2); i++)
        {
            printf("%ld ", arrar_aux[i]);
        }
        free(arrar_aux);
    }
    printf("\n");

    printf("Graph:\n");
    i = graph_print(stdout, g);
    printf("\n");

    graph_free(g);

    return 0;
}