#include "graph.h"
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

    for (i = 0; i < g->num_vertices; i++) // vemos si hay algun vertice con ese id
    {
        if (id == vertex_getId(g->vertices[i]))
        {
            vertex_index = i;
            break;
        }
    }

    if (vertex_index == -1) // no hay ningun vertice con ese id
    {
        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        if (g->connections[vertex_index][i] == TRUE)
        {
            count++; // contamos la veces donde este vertice tiene una conexion
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

    for (i = 0; i < MAX_VTX; i++) //comprobamos que el vertice este
    {
        if (vertex_getId(g->vertices[i]) == id)
        {
            break;
        }
    }
    if (i == MAX_VTX) //si no encontramos el vertice devuelve NULL
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

    while (fscanf(fin, "%i \n", &g->num_vertices) == 2);

    for (i = 0; i < g->num_vertices; i++)
    {
        fgets(descrip, MAX_TAM, fin);
        g->vertices[i] = vertex_initFromString(descrip);
    }

    while (fscanf(fin, "%i %i", &in1aux, &in2aux) == 2)
    {
        for (j=0; j<g->num_vertices; j++)
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

