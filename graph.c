#include "graph.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VTX 4096
#define MAX_TAM 100

struct _Graph
{
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};

Graph *graph_init()
{
    Graph *g = NULL;
    int i, j;

    g = (Graph *)malloc(sizeof(Graph));
    if (!g)
    {
        return NULL;
    }
    g->num_vertices = 0;
    g->num_edges = 0;
    for (i = 0; i < MAX_VTX; i++)
    {
        g->vertices[i] = NULL;
        for (j = 0; j < MAX_VTX; j++)
        {
            g->connections[i][j] = FALSE;
        }
    }
    return g;
}

void graph_free(Graph *g)
{
    int i;

    if (!g)
    {
        return;
    }

    for (i = 0; i < MAX_VTX; i++)
    {
        free(g->vertices[i]);
    }
    free(g);
}

Status graph_newVertex(Graph *g, char *desc)
{
    Vertex *v = NULL;
    int i;
    long id;

    if (!g || g->num_vertices == MAX_VTX)
    {
        return ERROR;
    }

    v = vertex_initFromString(desc);
    if (!v)
    {
        return ERROR;
    }

    id = vertex_getId(v);
    for (i = 0; i < g->num_vertices; i++)
    {
        if (id == vertex_getId(g->vertices[i]))
        {
            vertex_free(v);
            return ERROR;
        }
    }
    g->vertices[g->num_vertices] = v;
    vertex_setIndex(g->vertices[g->num_vertices], g->num_vertices);
    g->num_vertices++;
    return OK;
}

Bool graph_contains(const Graph *g, long id)
{
    int i;
    if (!g)
    {
        return FALSE;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (id == vertex_getId(g->vertices[i]))
        {
            return TRUE;
        }
    }
    return FALSE;
}

int graph_getNumberOfVertices(const Graph *g)
{
    if (!g)
    {
        return -1;
    }
    return g->num_vertices;
}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id)
{
    int i, count = 0, vertex_index = -1;

    if (!g)
    {
        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (id == vertex_getId(g->vertices[i]))
        {
            vertex_index = i;
            break;
        }
    }

    if (vertex_index == -1)
    {
        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[vertex_index][i] == TRUE)
        {
            count++;
        }
    }
    return count;
}

int graph_print(FILE *pf, const Graph *g)
{
    int i, j, chars_written = 0;

    if (!pf || !g)
    {
        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        chars_written += vertex_print(pf, g->vertices[i]);

        fprintf(pf, ": ");

        for (j = 0; j < g->num_vertices; j++)
        {
            if (g->connections[i][j] == TRUE)
            {
                chars_written += vertex_print(pf, g->vertices[j]);
                fprintf(pf, " ");
            }
        }
        fprintf(pf, "\n");
    }
    return chars_written;
}

Status graph_newEdge(Graph *g, long orig, long dest)
{

    int i, j;

    if (!g)
    {
        return ERROR;
    }
    for (i = 0; i < MAX_VTX; i++)
    {
        if (vertex_getId(g->vertices[i]) == orig)
        {
            break;
        }
    }
    if (i == MAX_VTX)
    {
        return ERROR;
    }

    for (j = 0; j < MAX_VTX; j++)
    {
        if (vertex_getId(g->vertices[j]) == dest)
        {
            break;
        }
    }
    if (j == MAX_VTX)
    {
        return ERROR;
    }

    g->connections[i][j] = TRUE;
    g->num_edges++;
    return OK;
}

int graph_getNumberOfEdges(const Graph *g)
{

    int i, j, num_con = 0;

    if (!g)
    {
        return -1;
    }

    for (i = 0; i < MAX_VTX; i++)
    {
        for (j = 0; j < MAX_VTX; j++)
        {
            if (g->connections[i][j] == TRUE)
                num_con++;
        }
    }
    return num_con;
}

Bool graph_connectionExists(const Graph *g, long orig, long dest)
{

    int i, j;

    if (!g)
    {
        return FALSE;
    }

    for (i = 0; i < MAX_VTX; i++)
    {
        if (vertex_getId(g->vertices[i]) == orig)
        {
            break;
        }
    }
    if (i == MAX_VTX)
    {
        return FALSE;
    }

    for (j = 0; j < MAX_VTX; j++)
    {
        if (vertex_getId(g->vertices[j]) == dest)
        {
            break;
        }
    }
    if (j == MAX_VTX)
    {
        return FALSE;
    }

    if (g->connections[i][j] == TRUE)
    {
        return TRUE;
    }
    return FALSE;
}

long *graph_getConnectionsFromId(const Graph *g, long id)
{

    int i, k, n_conec = 0;
    long *conec = NULL;

    if (!g)
    {
        return NULL;
    }

    for (i = 0; i < MAX_VTX; i++)
    {
        if (vertex_getId(g->vertices[i]) == id)
        {
            break;
        }
    }
    if (i == MAX_VTX)
    {
        return NULL;
    }

    for (k = 0; k < MAX_VTX; k++)
    {
        if (g->connections[i][k] == TRUE)
            n_conec++;
    }

    if (!(conec = (long *)calloc(n_conec, sizeof(long))))
    {
        return NULL;
    }

    n_conec = 0;
    for (k = 0; k < MAX_VTX; k++)
    {
        if (g->connections[i][k] == TRUE)
        {
            conec[n_conec] = vertex_getId(g->vertices[k]);
            n_conec++;
        }
    }
    return conec;
}

int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag)
{

    int i, j, count = 0;

    if (!g)
    {
        return -1;
    }

    for (i = 0; i < MAX_VTX; i++)
    {
        if (!strcmp(vertex_getTag(g->vertices[i]), tag))
        {
            break;
        }
    }
    if (i == MAX_VTX)
    {
        return -1;
    }

    for (j = 0; j < MAX_VTX; j++)
    {
        if (g->connections[i][j] == TRUE)
            count++;
    }
    return count;
}

long *graph_getConnectionsFromTag(const Graph *g, char *tag)
{

    int i, k, n_conec = 0;
    long *conec = NULL;

    if (!g || !tag)
    {
        return NULL;
    }

    for (i = 0; i < MAX_VTX; i++)
    {
        if (!strcmp(vertex_getTag(g->vertices[i]), tag))
        {
            break;
        }
    }
    if (i == MAX_VTX)
    {
        return NULL;
    }

    for (k = 0; k < MAX_VTX; k++)
    {
        if (g->connections[i][k] == TRUE)
            n_conec++;
    }

    if (!(conec = (long *)calloc(n_conec, sizeof(long))))
    {
        return NULL;
    }

    n_conec = 0;
    for (k = 0; k < MAX_VTX; k++)
    {
        if (g->connections[i][k] == TRUE)
        {
            conec[n_conec] = vertex_getId(g->vertices[k]);
            n_conec++;
        }
    }
    return conec;
}

Status graph_readFromFile(FILE *fin, Graph *g)
{
    int i, in1aux, in2aux, j;
    long pos1, pos2;
    char descrip[MAX_TAM];

    if (!fin || !g)
    {
        return ERROR;
    }

    while (fscanf(fin, "%i \n", &g->num_vertices) == 2)
        ;

    for (i = 0; i < g->num_vertices; i++)
    {
        fgets(descrip, MAX_TAM, fin);
        g->vertices[i] = vertex_initFromString(descrip);
        vertex_setIndex(g->vertices[i], i);
    }

    while (fscanf(fin, "%i %i", &in1aux, &in2aux) == 2)
    {
        for (j = 0; j < g->num_vertices; j++)
        {
            if (in1aux == vertex_getId(g->vertices[j]))
            {
                pos1 = j;
            }

            if (in2aux == vertex_getId(g->vertices[j]))
            {
                pos2 = j;
            }
        }
        g->connections[pos1][pos2] = TRUE;
    }
    return OK;
}

Vertex *graph_get_vertex_from_index(Graph *graph, int index)
{
    int i;

    if (!graph || index < 0)
    {
        return NULL;
    }
    for (i = 0; i < graph->num_vertices; i++)
    {
        if (vertex_getIndex(graph->vertices[i]) == index)
        {
            return graph->vertices[i];
        }
    }
    return NULL;
}

Vertex *graph_get_vertex_from_id(Graph *g, long id)
{
    int i = 0;
    if (g == NULL)
    {
        return NULL;
    }
    if (graph_contains(g, id) == FALSE)
    {
        return NULL;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (vertex_getId(g->vertices[i]) == id)
        {
            return g->vertices[i];
        }
    }
    return NULL;
}

/**
 * @brief: Makes a search from the origin vertex to the destination vertex of a
graph using the depth-first search algorithm
 * using an ADT Stack
 *
 * The function prints each visited vertex while traversing the graph
 *
 * @param g, Pointer to graph
 * @param from_id, id of the origin Vertex
 * @param to_id, id of the destination Vertex
 * @return The function returns OK or ERROR
**/
Status graph_depthSearch(Graph *g, long from_id, long to_id)
{
    int i;
    Stack *stack = NULL;
    Status status = OK;
    Vertex *vf = NULL, *vt = NULL, *v_aux = NULL;
    long *adjacent_ids = NULL;
    int num_connections;

    if (g == NULL || from_id <= 0 || to_id <= 0)
    {
        return ERROR;
    }

    for (i = 0; i < graph_getNumberOfVertices(g); i++)
    {
        vertex_setState(g->vertices[i], WHITE);
    }

    stack = stack_init();
    if (stack == NULL)
    {
        return ERROR;
    }

    vf = graph_get_vertex_from_id(g, from_id);
    vt = graph_get_vertex_from_id(g, to_id);

    if (!vf || !vt)
    {
        stack_free(stack);
        return ERROR;
    }
    vertex_setState(vf, BLACK);

    stack_push(stack, vf);

    while ((stack_isEmpty(stack) == FALSE) && (status == OK))
    {
        v_aux = (Vertex *)stack_pop(stack);
        vertex_print(stdout, v_aux);
        fprintf(stdout, "\n");

        if (vertex_cmp(v_aux, vt) == 0)
        {
            stack_free(stack);
            return status;
        }
        else
        {
            if (!(adjacent_ids = graph_getConnectionsFromId(g, vertex_getId(v_aux))))
            {
                continue;
            }

            num_connections = graph_getNumberOfConnectionsFromId(g, vertex_getId(v_aux));
            for (i = 0; i < num_connections; i++)
            {
                if (vertex_getState(graph_get_vertex_from_id(g, adjacent_ids[i])) == WHITE)
                {
                    vertex_setState(graph_get_vertex_from_id(g, adjacent_ids[i]), BLACK);
                    stack_push(stack, graph_get_vertex_from_id(g, adjacent_ids[i]));
                }
            }
            free(adjacent_ids);
        }
    }

    stack_free(stack);
    return status;
}
