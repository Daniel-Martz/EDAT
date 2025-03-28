#include "vertex.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct _Vertex {
    long id;
    char tag[TAG_LENGTH];
    Label state;
    int  index;
};

Status vertex_setField(Vertex *v, char *key, char *value) {
    if (!key || !value) return ERROR;

    if (strcmp(key, "id") == 0) {
        return vertex_setId(v, atol(value));
    } else if (strcmp(key, "tag") == 0) {
        return vertex_setTag(v, value);
    } else if (strcmp(key, "state") == 0) {
        return vertex_setState(v, (Label)atoi(value));
    }

    return ERROR;
}

Vertex *vertex_init() {
    Vertex *v = NULL;
    if (!(v = (Vertex *)calloc(1, sizeof(Vertex)))) {
        return NULL;
    }
    v->id = 0;
    strcpy(v->tag, "");
    v->state = WHITE;
    v->index = 0;
    return v;
}

Vertex *vertex_initFromString(char *descr) {
    char buffer[1024];
    char *token;
    char *key;
    char *value;
    char *p;
    Vertex *v;

    if (!descr) return NULL;

    v = vertex_init();
    if (!v) return NULL;

    sprintf(buffer, "%s", descr);
    token = strtok(buffer, " \t\n");
    
    while (token) {
        p = strchr(token, ':');
        if (!p) continue;

        *p = '\0';
        key = token;
        value = p + 1;

        vertex_setField(v, key, value);

        token = strtok(NULL, " \t\n");
    }

    return v;
}

void vertex_free(void *v) {
    free(v);
}

long vertex_getId(const Vertex *v) {
    if (v == NULL) return -1;
    return v->id;
}

const char *vertex_getTag(const Vertex *v) {
    if (v == NULL) return NULL;
    return v->tag;
}

Label vertex_getState(const Vertex *v) {
    if (v == NULL) return ERROR_VERTEX;
    return v->state;
}

Status vertex_setId(Vertex *v, const long id) {
    if (v == NULL || id < 0) return ERROR;
    v->id = id;
    return OK;
}

Status vertex_setTag(Vertex *v, const char *tag) {
    if (v == NULL || tag == NULL) return ERROR;
    strcpy(v->tag, tag);
    return OK;
}

Status vertex_setIndex(Vertex *v, const int ind){
    if(v == NULL || (ind < 0)){
        return ERROR;
    }
    v->index = ind;
    return OK;
}   

int vertex_getIndex(Vertex *v){
    if (v== NULL)
    {
    return -1;
    }
    return v->index;
}

Status vertex_setState(Vertex *v, const Label state) {
    if (v == NULL) return ERROR;
    v->state = state;
    return OK;
}

int vertex_cmp(const void *v1, const void *v2) {
    Vertex *w1 = (Vertex *)v1;
    Vertex *w2 = (Vertex *)v2;
    long diffid = w1->id - w2->id;

    if (diffid) return diffid;
    return strcmp(w1->tag, w2->tag);
}

void *vertex_copy(const void *src) {
    Vertex *trg, *srd;
    srd = (Vertex *)src;
    trg = vertex_init();
    if (trg == NULL) return NULL;

    trg->id = srd->id;
    trg->state = srd->state;
    strcpy(trg->tag, srd->tag);
    trg->index = srd->index;

    return trg;
}

int vertex_print(FILE *pf, const void *v) {
    int total_chars = 0;
    Vertex *w;

    if (pf == NULL || v == NULL)
    {
        return -1;
    }

    w = (Vertex *)v;
    total_chars = fprintf(pf, "[%ld, %s, %d, %d]", w->id, w->tag, w->state, w->index);
    
    return total_chars;
}

