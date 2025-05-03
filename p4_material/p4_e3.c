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

int main(int argc, const char **argv)
{
    int nums = 0, i, num_res = 0;
    SearchQueue *s = NULL;
    FILE *f = NULL;
    float *e_aux = NULL, media = 0, mediana = 0, sum = 0, lowest_aux[TAM], highest_aux[TAM], **elements = NULL;

    if (argc < 1)
    {
        fprintf(stderr, "Debe introducir: %s <Fichero entrada>", argv[0]);
        return -1;
    }


    if (!(f = fopen(argv[1], "r")))
    {
        fprintf(stderr, "No fue posible abrir el archivo %s ", argv[1]);
        return -1;
    }

    s = search_queue_new(float_print, float_cmp);
    if (s == NULL)
    {
        fprintf(stderr, "Hubo un problema iniciando la cola");
        fclose(f);
        return -1;
    }

    fscanf(f, "%i", &nums);
    fgetc(f);

    if(nums<=0){
        fprintf(stderr, "El numero de elementos (%i) ndicado en el archivo no es válido", nums);
        fclose(f);
        search_queue_free(s);
        return -1;
    }

    if(!(elements = (float**)calloc(nums, sizeof(float*)))){
        fprintf(stderr, "Hubo un problema iniciando el array de elementos");
        fclose(f);
        search_queue_free(s);
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
            fprintf(stderr, "Hubo un problema reservando memoria para los elementos");
            return -1;
        }
        
        fscanf(f,"%f", &(*e_aux));
        if(search_queue_push(s, e_aux) == ERROR){
            fprintf(stderr, "There was an error pushing a queue element");
            return -1;
        }
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
            if(i==0 || i==1 || i==2){
                lowest_aux[i] = *e_aux;
            }
            
            sum += *elements[i];
            if(search_queue_push(s, e_aux) == ERROR){
                fprintf(stderr, "There was an error pushing a queue element");
                return -1;
            }
        }
    }
    else{

        for(i = 0; i< nums; i++){
            if(!(e_aux = search_queue_pop(s))){
                fprintf(stderr, "There was an error extracting a queue element");
                return -1;
            }
            if(i == ((nums/2)-1)){
                mediana = *e_aux;
            }
            if(i == (nums/2)){
                mediana += *e_aux;
                mediana /= 2;
            }
            if(i==0 || i==1 || i==2){
                lowest_aux[i] = *e_aux;
            }
            else if(i>=nums/2){
                if(search_queue_push(s, e_aux) == ERROR){
                    fprintf(stderr, "There was an error pushing a queue element");
                    return -1;
                }
            }
            sum += *elements[i];
        }
    }
    num_res = nums - TAM;

    if(num_res < 0){
        num_res = 0;
    }

    if(num_res > 3){
        num_res = 3;
    }

    for(i = 0; i<num_res; i++){
        if(!(e_aux = search_queue_popBack(s))){
            fprintf(stderr, "There was an error extracting a queue element");
            return -1;
        }
        highest_aux[i] = *e_aux;
    }
        
    media = sum/nums;
    
    fprintf(stdout, "Mean: %.2f\n", media);
    fprintf(stdout, "Median: %.2f\n", mediana);
        
    fprintf(stdout, "Lowest grades: ");
    for(i=0; i<TAM; i++){
        fprintf(stdout, "%.2f ", lowest_aux[i]);
    }
    if(num_res == 0){
        fprintf(stdout, "\nThere aren`t more numbers ");
    }
    fprintf(stdout, "\nHighest grades: ");
    for(i=0; i<num_res; i++){
        fprintf(stdout, "%.2f ", highest_aux[i]);
    }

    fclose(f);
    
    search_queue_free(s);

    for(i = 0; i < nums; i++) {
        free(elements[i]);
    }
    free(elements);
    return 0;
}
