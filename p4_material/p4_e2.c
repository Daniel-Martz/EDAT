#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bstree.h"
#include "types.h"
#include "vertex.h"
#include "search_queue.h"
#include "file_utils.h"


int main(int argc, char **argv)
{
    FILE *salida = NULL;
    SearchQueue *s_queue = NULL;
    P_ele_print print = string_print;
    P_ele_cmp cmp = string_cmp;

    if (argc < 3)
    {
        fprintf(stderr, "Debe introducir: %s <Fichero entrada> <Fichero salida>", argv[0]);
        return -1;
    }

    if (!(salida = fopen(argv[2], "w")))
    { 
        fprintf(stderr, "Error: No se pudo abrir el fichero de salida: %s\n", argv[2]);
        return -1;
    }

    s_queue = search_queue_new(print, cmp);
    if (s_queue == NULL)
    {
        fprintf(stderr, "Error: No se pudo crear la cola de búsqueda.\n");
        fclose(salida);
        return -1;
    }

    if (read_tad_from_file((void *)s_queue, argv[1], (elem_from_string)str2str, (tad_insert)search_queue_push, (tad_isEmpty)search_queue_isEmpty) == ERROR)
    {
        fprintf(stderr, "Error: No se pudo leer el TAD desde el fichero de entrada: %s\n", argv[1]);
        search_queue_free_and_elements(s_queue);
        fclose(salida);
        return -1;
    }

    if (search_queue_print(salida, s_queue) < 0)
    {
        fprintf(stderr, "Error: No se pudo imprimir la cola de búsqueda en el fichero de salida.\n");
        search_queue_free_and_elements(s_queue);
        fclose(salida);
        return -1;
    }

    search_queue_free_and_elements(s_queue);
    fclose(salida);
    return 0;
}

  