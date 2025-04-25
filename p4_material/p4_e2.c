#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bstree.h"
#include "types.h"
#include "vertex.h"
#include "search_queue.h"
#include "file_utils.h"

#define TAM 50

int main(int argc, char **argv)
{
    FILE *entrada = NULL, *salida = NULL;
    char frase[TAM];
    char *linea = NULL, *p = NULL;
    SearchQueue *s = NULL;
    P_ele_print print = string_print;
    P_ele_cmp cmp = string_cmp;

    if (argc < 3)
    {
        fprintf(stderr, "Debe introducir: %s <Fichero entrada> <Fichero salida>", argv[0]);
        return -1;
    }

    if (!(entrada = fopen(argv[1], "r")))
    {
        return -1;
    }

    if (!(salida = fopen(argv[2], "w")))
    {
        fclose(entrada);
        return -1;
    }

    s = search_queue_new(print, cmp);
    if (s == NULL)
    {
        fclose(entrada);
        fclose(salida);
        return -1;
    }

    p = fgets(frase, TAM, entrada);
    search_queue_push(s, p);

    while (p != NULL)
    {
        p = fgets(frase, TAM, entrada);
        search_queue_push(s, p);
    }

    search_queue_print(salida, s);

    search_queue_free(s);

    fclose(entrada);
    fclose(salida);
    return 0;
}
