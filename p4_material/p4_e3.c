#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bstree.h"
#include "types.h"
#include "vertex.h"
#include "search_queue.h"
#include "file_utils.h"



int main(int argc, const char **argv)
{
    int nums = 0, i;
    float *f = NULL;
    SearchQueue *s = NULL;
    FILE *f = NULL;
    double *e_aux = NULL, media = 0, mediana = 0;

    if (argc < 2)
    {
        fprintf(stderr, "Debe introducir: %s <Fichero entrada>", argv[0]);
        return -1;
    }

    if (!(f = fopen(argv[1], "r")))
    {
        return -1;
    }

    s = search_queue_new(float_print, float_cmp);
    if (s == NULL)
    {
        fclose(f);
        return -1;
    }

    fscanf(f, "%i", &nums);
    fgetc(f);

    for (i = 0; i < nums; i++)
    {
        e_aux = (double*)malloc(sizeof(double)); 
        if (e_aux == NULL)
        {
            fclose(f); 
            search_queue_free(s);
            return NULL;
        }
        
        fscanf(f,"%lf", &(*e_aux));
        search_queue_push(s, (void*) e_aux);
    }

    search_queue_print(stdout, s);

    fgets

return 0;
}