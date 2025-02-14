#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VTX 4096

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
    int i, j;

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

    for (i = 0; i < g->vertices; i++)
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

    for (i=0; i<g->vertices; i++)
    {
        chars_written += vertex_print(pf, g->vertices[i]);

        fprintf (pf, ": ");
        
        for (j=0; j<g->num_vertices;i++)
        {
            if (g->connections[i][j]==TRUE)
            {
                chars_written += vertex_print(pf, g->vertices[j]);
                fprintf (pf, " ");
            }
        }
        fprintf (pf, "\n");
    }
    return chars_written;
}


/**
 * @brief Creates an edge between to vertices of a graph.
 *
 * If any of the two vertices does not exist in the graph the edge is
 * not created.
 *
 * @param g Pointer to the graph.
 * @param orig ID of the origin vertex.
 * @param dest ID of the destination vertex.
 *
 * @return OK if the edge could be added to the graph, ERROR otherwise.
 **/
Status graph_newEdge(Graph *g, long orig, long dest){

    int i,j;

    if(!g){
        return ERROR;
    }
    for(i=0; i<MAX_VTX; i++){
        if(vertex_getId(g->vertices[i])==orig)
        {
            break;
        }
    }
    if(i == MAX_VTX){
        return ERROR;
    }

    for(j=0; j<MAX_VTX; j++){
        if(vertex_getId(g->vertices[j])==dest)
        {
            break;
        }
    }
    if(j == MAX_VTX){
        return ERROR;
    }

    g->connections[i][j] = TRUE;
    g->num_edges++;
    return OK;
}

/**
 * @brief Checks if a graph contains a vertex.
 *
 * @param g Pointer to the graph.
 * @param id ID of the vertex.
 *
 * @return Returns TRUE if there is a vertex in the graph g with the
 * ID id, FALSE otherwise.
 **/
Bool graph_contains(const Graph *g, long id){
    
    int i;

    if(!g){
        return FALSE;
    }
    for(i=0; i<MAX_VTX; i++){
        if(vertex_getId(g->vertices[i]) == id){
            return TRUE;
        }
    }
    return FALSE;
}


/**
 * @brief Returns the total number of edges  * in the graph.
 *
 * @param g Pointer to the graph.
 *
 * @return Returns The number of vertices in the graph, or -1 if 
 * there is any error.
 **/
int graph_getNumberOfEdges(const Graph *g){
    
    int i,j,num_con = 0;
    
    if(!g){
        return -1;     
    }

    for(i=0; i<MAX_VTX; i++)
    {
        for(j=0; j<MAX_VTX; j++)
        {
            if(g->connections[i][j] == TRUE)
                num_con++;

        }
    }
    return num_con;
}

/**
 * @brief Determines if there is a connection between a pair of vertices.
 *
 * @param g Pointer to the graph.
 * @param orig ID of the origin vertex.
 * @param dest ID of the destination vertex.
 *
 * @return Returns TRUE if there is a connection in g from orig
 *  to dest, FALSE otherwise.
 **/
Bool graph_connectionExists(const Graph *g, long orig, long dest){
    
    int i,j;

    if(!g){
        return FALSE;
    }

    for(i=0; i<MAX_VTX; i++){
        if(vertex_getId(g->vertices[i]) == orig)
        {
            break;
        }
    }
    if(i == MAX_VTX){
        return FALSE;
    }

    for(j=0; j<MAX_VTX; j++){
        if(vertex_getId(g->vertices[j]) == dest)
        {
            break;
        }
    }
    if(j == MAX_VTX){
        return FALSE;
    }

   if(g->connections[i][j] == TRUE){
    return TRUE;
   }
   return FALSE;
}

/**
 * @brief Returns an array with the ids of all the vertices which a 
 * given vertex connects to.
 *
 * This function allocates memory for the array.
 *
 * @param g Pointer to the graph.
 * @param id ID of the origin vertex.
 *
 * @return Returns an array with the ids of all the vertices to which 
 * the vertex with ID id is connected, or NULL if there is any error.
 */
long *graph_getConnectionsFromId(const Graph *g, long id){
    
    int i,k,n_conec = 0;
    long *conec = NULL;

    if(!g){
        return NULL;
    }

    for(i=0; i<MAX_VTX; i++){
        if(vertex_getId(g->vertices[i]) == id){
            break;
        }
    }
    if(i == MAX_VTX){
        return NULL;
    }

    for(k=0; k<MAX_VTX; k++){
        if(g->connections[i][k] == TRUE)
            n_conec++;
    }

    if(!(conec=(long*)calloc(n_conec,sizeof(long)))){
        return NULL;
    }

    n_conec = 0;
    for(k=0; k<MAX_VTX; k++){
        if(g->connections[i][k] == TRUE){
            conec[n_conec] = vertex_getId(g->vertices[k]);
            n_conec++;
        }
    }
    return conec;
}

/**
 * @brief Gets the number of connections starting at a given vertex.
 *
 * @param g Pointer to the graph.
 * @param tag Tag of the origin vertex.
 *
 * @return Returns the total number of connections starting at 
 * vertex with Tag tag, or -1 if there is any error.
 **/
int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag){

    int i,j,count = 0;

    if(!g){
        return -1;
    }

    for(i=0; i<MAX_VTX; i++){
        if(!strcmp(vertex_getTag(g->vertices[i]),tag)){
            break;
        }
    }
    if(i == MAX_VTX){
        return -1;
    }
    
    for(j=0; j<MAX_VTX;j++){
        if(g->connections[i][j] == TRUE)
            count++;
    }
    return count;   
}

/**
 * @brief Returns an array with the ids of all the vertices which a 
 * given vertex connects to.
 *
 * This function allocates memory for the array.
 *
 * @param g Pointer to the graph.
 * @param tag Tag of the origin vertex.
 *
 * @return Returns an array with the ids of all the vertices to which 
 * the vertex with Tag tag is connected, or NULL if there is any error.
 */
long *graph_getConnectionsFromTag(const Graph *g, char *tag){
    
    int i,k,n_conec = 0;
    long *conec = NULL;

    if(!g || !tag){
        return NULL;
    }

    for(i=0; i<MAX_VTX; i++){
        if(!strcmp(vertex_getTag(g->vertices[i]),tag)){
            break;
        }
    }
    if(i == MAX_VTX){
        return NULL;
    }

    for(k=0; k<MAX_VTX; k++){
        if(g->connections[i][k] == TRUE)
            n_conec++;
    }

    if(!(conec=(long*)calloc(n_conec,sizeof(long)))){
        return NULL; 
    }

    n_conec = 0;
    for(k=0; k<MAX_VTX; k++){
        if(g->connections[i][k] == TRUE){
            conec[n_conec] = vertex_getId(g->vertices[k]);
            n_conec++;
        }
    }
    return conec;
}

/**
 * @brief Reads a graph definition from a text file.
 *
 * Reads a graph description from the text file pointed to by fin,
 * and fills the graph g.
 *
 * The first line in the file contains the number of vertices.
 * Then one line per vertex with the vertex description.  
 * Finally one line per connection, with the ids of the origin and 
 * the destination. 
 *
 * For example:
 *
 * 4
 * id:1 tag:Madrid
 * id:2 tag:Toledo
 * id:3 tag:Avila
 * id:4 tag:Segovia
 * 1 2
 * 1 3
 * 2 4
 * 4 3
 *
 * @param fin Pointer to the input stream.
 * @param g Pointer to the graph.
 *
 * @return OK or ERROR
 */
Status graph_readFromFile (FILE *fin, Graph *g){
    
    int i,in1aux,in2aux;
    char tagaux[TAG_LENGTH];

    if(!fin || !g){
        return ERROR;
    }

    if(fscanf(fin,"%i",&g->num_vertices) != 1){
        return ERROR;
    }

    for(i=0; i<g->num_vertices; i++){
        fgets(tagaux, TAG_LENGTH, fin);
        g->vertices[i] = vertex_initFromString(tagaux);
    }

    while(fscanf(fin, "%i %i", &in1aux,&in2aux) == 2){
        if((in1aux >= MAX_VTX) || (in2aux >= MAX_VTX)){
            return ERROR;
        }
        g->connections[in1aux][in2aux] = TRUE;
    }
}

/* CUIDADO CON LAS FUNCIONES GET CONECTIONSFROMTAG Y LA DE ID, QUE NO SE LIBERA MEMORIA*/
