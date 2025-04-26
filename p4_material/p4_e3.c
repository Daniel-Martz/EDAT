#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bstree.h"
#include "types.h"
#include "vertex.h"
#include "search_queue.h"
#include "file_utils.h"

#define TAM 3

void free_elements(SearchQueue *s){
    void *e_aux = NULL;
    if(!s) return;

    while(search_queue_isEmpty(s) == FALSE){
        e_aux = search_queue_pop(s);
        free((float*)e_aux);
    }
}

int main(int argc, const char **argv)
{
    int nums = 0, i;
    SearchQueue *s = NULL, *s_aux = NULL;
    FILE *f = NULL;
    float *e_aux = NULL, media = 0, mediana = 0, sum = 0, lowest_aux[TAM], highest_aux[TAM], **elements = NULL;

    if (argc < 1)
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

    s_aux = search_queue_new(float_print, float_cmp);
    if (s_aux == NULL)
    {
        fclose(f);
        search_queue_free(s);
        return -1;
    }

    fscanf(f, "%i", &nums);
    fgetc(f);

    if(!(elements = (float**)calloc(nums, sizeof(float*)))){
        fclose(f);
        search_queue_free(s);
        search_queue_free(s_aux);
        return -1;
    }

    for (i = 0; i < nums; i++)
    {
        e_aux = NULL;
        e_aux = (float*)malloc(sizeof(float));
        if (e_aux == NULL)
        {
            fclose(f); 
            search_queue_free(s);
            search_queue_free(s_aux);
            return -1;
        }
        
        fscanf(f,"%f", &(*e_aux));
        search_queue_push(s, (void*)e_aux);
        search_queue_push(s_aux, (void*)e_aux);
        elements[i] = e_aux;
    }

    fprintf(stdout, "Ordered grades: ");
    search_queue_print(stdout, s);

    if(nums%2){
        for(i = 0; i< nums; i++){
            e_aux = search_queue_pop(s);
            if(i == (nums/2)){
                mediana = *e_aux;
            }

            if(i == 0 || i == 1 || i == 2){
                lowest_aux[i] = *e_aux;
            }
            sum += *e_aux;
        }
    }
    else{
        for(i = 0; i< nums; i++){
            e_aux = search_queue_pop(s);
            if(i == ((nums/2) -1)){
                mediana = *e_aux;
            }
            if(i == (nums/2)){
                mediana += *e_aux;
                mediana /= 2;
            }
            if(i == 0 || i == 1 || i == 2){
                lowest_aux[i] = *e_aux;
            }
            sum += *e_aux;
        }
    }

    
    for(i = 0; i<TAM; i++){
        e_aux = search_queue_popBack(s_aux);
        highest_aux[i] = *e_aux;
    }
    
    media = sum/nums;
    
    fprintf(stdout, "Mean: %.2f\n", media);
    fprintf(stdout, "Median: %.2f\n", mediana);
    
    fprintf(stdout, "Lowest grades: ");
    for(i=0; i<TAM; i++){
        fprintf(stdout, "%.2f ", lowest_aux[i]);
    }
    
    fprintf(stdout, "\nHighest grades: ");
    for(i=0; i<TAM; i++){
        fprintf(stdout, "%.2f ", highest_aux[i]);
    }
    
    fclose(f);

    for (i = 0; i < nums; i++) {
        free(elements[i]);
    }
    free(elements);
    
    search_queue_free(s);
    search_queue_free(s_aux);
    return 0;
}