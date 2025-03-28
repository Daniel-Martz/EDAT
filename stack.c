#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 2
#define FCT_CAPACITY 2

struct _Stack {
    void **item;    /* Array de elementos */
    int top;        /* Índice del elemento superior */
    int capacity;   /* Capacidad actual del stack */
};

Stack *stack_init() {
    Stack *s = NULL;
    
    s = (Stack *)calloc(1, sizeof(Stack));
    if (!s) return NULL;

    s->item = (void **)calloc(INIT_CAPACITY, sizeof(void *));
    if (!s->item) {
        free(s);
        return NULL;
    }
    
    s->top = -1;  // Pila vacía
    s->capacity = INIT_CAPACITY;
    
    return s;
}

void stack_free(Stack *s) {
    if (!s) return;
    
    // No liberamos los elementos porque no son propiedad de la pila
    free(s->item);
    free(s);
}

Status stack_push(Stack *s, const void *ele) {
    if (!s || !ele) return ERROR;

    // Redimensionar si es necesario
    if (s->top == s->capacity - 1) {
        size_t new_capacity = s->capacity * FCT_CAPACITY;
        void **new_items = realloc(s->item, new_capacity * sizeof(void *));
        if (!new_items) return ERROR;
        
        s->item = new_items;
        s->capacity = new_capacity;
    }
    
    s->top++;
    s->item[s->top] = (void *)ele;  // Almacenamos el puntero (sin copiar)
    
    return OK;
}

void *stack_pop(Stack *s) {
    if (!s || stack_isEmpty(s)) return NULL;
    
    void *ele = s->item[s->top];
    s->top--;
    
    return ele;
}

void *stack_top(const Stack *s) {
    if (!s || stack_isEmpty(s)) return NULL;
    return s->item[s->top];
}

Bool stack_isEmpty(const Stack *s) {
    return (!s || s->top == -1);
}

size_t stack_size(const Stack *s) {
    if (!s) return 0;
    return s->top + 1;
}

int stack_print(FILE *fp, const Stack *s, P_stack_ele_print f) {
    int total = 0;
    if (!fp || !s || !f) return -1;
    

    for (int i = s->top; i >= 0; i--) {  
        total += f(fp, s->item[i]);
    }
    
    return total;
}
