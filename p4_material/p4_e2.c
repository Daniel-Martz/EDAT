#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bstree.h"
#include "types.h"
#include "vertex.h"
#include "search_queue.h"
#include "file_utils.h"

void free_elements(SearchQueue *s)
{
    void *e_aux = NULL;

    if (!s)
        return;

    
    while (search_queue_isEmpty(s) == FALSE)
    {   
        e_aux = search_queue_pop(s);
        
        if (e_aux)
        {
        
            free((char*)e_aux);  
        }
    }
}



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
        return -1;
    }

    s_queue = search_queue_new(print, cmp);
    if (s_queue == NULL)
    {
        fclose(salida);
        return -1;
    }

    if (read_tad_from_file((void *)s_queue, argv[1], (elem_from_string)str2str, (tad_insert)search_queue_push, (tad_isEmpty)search_queue_isEmpty) == ERROR)
    {
        search_queue_free(s_queue);
        fclose(salida);
        return -1;
    }

    search_queue_print(salida, s_queue);

    free_elements(s_queue);
    search_queue_free(s_queue);

    fclose(salida);
    return 0;
}
