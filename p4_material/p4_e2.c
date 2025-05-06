#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bstree.h"
#include "types.h"
#include "vertex.h"
#include "search_queue.h"
#include "file_utils.h"

#define MAX 5000

int main(int argc, char **argv)
{
    FILE *salida = NULL, *entrada = NULL;
    SearchQueue *s_queue = NULL;
    P_ele_print print = string_print;
    P_ele_cmp cmp = string_cmp;
    char **strings = NULL, *line = NULL;
    Status status = OK;
    int i = 0, j = 0, num = 0;

    if (argc < 3)
    {
        fprintf(stderr, "Debe introducir: %s <Fichero entrada> <Fichero salida>\n", argv[0]);
        return -1;
    }

    if (!(entrada = fopen(argv[1], "r")))
    {
        fprintf(stderr, "Error: No se pudo abrir el fichero de entrada: %s\n", argv[1]);
        return -1;
    }

    if (!(salida = fopen(argv[2], "w")))
    {
        fprintf(stderr, "Error: No se pudo abrir el fichero de salida: %s\n", argv[2]);
        fclose(entrada);
        return -1;
    }

    s_queue = search_queue_new(print, cmp);
    if (s_queue == NULL)
    {
        fprintf(stderr, "Error: No se pudo crear la cola de búsqueda.\n");
        fclose(entrada);
        fclose(salida);
        return -1;
    }

    line = (char *)malloc(MAX * sizeof(char));
    if (!line)
    {
        fprintf(stderr, "Error al reservar memoria para la línea.\n");
        fclose(entrada);
        fclose(salida);
        search_queue_free(s_queue);
        return -1;
    }

    strings = (char **)malloc(MAX * sizeof(char *));
    if (strings == NULL)
    {
        fprintf(stderr, "Error al reservar memoria para los strings.\n");
        fclose(entrada);
        fclose(salida);
        search_queue_free(s_queue);
        free(line);
        return -1;
    }

    while (fgets(line, MAX, entrada) && status == OK)
    {
        line[strcspn(line, "\n")] = '\0';
        strings[i] = malloc(strlen(line) + 1);
        if (strings[i] == NULL)
        {
            fprintf(stderr, "Error al reservar memoria para la línea %d.\n", i);
            fclose(entrada);
            fclose(salida);
            search_queue_free(s_queue);
            free(line);
            for (j = 0; j < i; j++)
            {
                free(strings[j]);
            }
            free(strings);
            return -1;
        }
        strcpy(strings[i], line);
        status = search_queue_push(s_queue, strings[i]);
        i++;
    }
    num = i;

    if (status == ERROR)
    {
        fprintf(stderr, "Error mientras se añaden los elementos a la cola.\n");
        fclose(entrada);
        fclose(salida);
        search_queue_free(s_queue);
        free(line);
        for (i = 0; i < num; i++)
            free(strings[i]);
        free(strings);
        return -1;
    }

    search_queue_print(salida, s_queue);

    fclose(entrada);
    fclose(salida);

    for (i = 0; i < num; i++)
    {
        free(strings[i]);
    }
    free(strings);
    free(line);
    search_queue_free(s_queue);
    return 0;
}
