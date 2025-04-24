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
    char *f;
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
        flcose(salida);
        return -1;
    }

    while(fgets(frase, TAM, entrada))
    return 0;
}