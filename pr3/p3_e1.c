#include "delivery.h"
#include "vertex.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 250

/**
 * @brief Builds a delivery from the information read on the file.
 *
 * @param pf File descriptor. The file should contain the following information:
 * First line: delivery_name product_name
 * Second line: number of cities/vertices
 * Following lines: vertices description
 *
 * @return A pointer to the fulfilled delivery. If there have been errors
returns NULL.
 */
Delivery *build_delivery(FILE *pf)
{
   Delivery *delivery = NULL;
   Vertex *vertex_aux = NULL;
   char del_name[SIZE], del_product[SIZE];
   int num_cities, i;
   char desc[SIZE];

   if (pf == NULL)
   {
      return NULL;
   }

   if (fscanf(pf, "%s %s", del_name, del_product) != 2)
   {
      return NULL;
   }

   delivery = delivery_init(del_name, del_product);
   if (!delivery)
   {
      return NULL;
   }

   if (fscanf(pf, "%d", &num_cities) != 1)
   {
      delivery_free(delivery);
      return NULL;
   }

   fgetc(pf);

   for (i = 0; i < num_cities; i++)
   {
      if (!fgets(desc, SIZE, pf))
      {
         delivery_free(delivery);
         return NULL;
      }
      
      vertex_aux = vertex_initFromString(desc);
      {
         if (!vertex_aux)
         {
            delivery_free(delivery);
            return NULL;
         }
      }

      if (delivery_add(stdout, delivery, vertex_aux, vertex_print) == ERROR)
      {
         vertex_free(vertex_aux);
         delivery_free(delivery);
         return NULL;
      }
   }

   return delivery;
}

int main(int argc, char **argv)
{
   Delivery *delivery = NULL;
   char filename[SIZE];
   FILE *f = NULL;

   if (argc < 2)
   {
      fprintf(stderr, "Debe introducir: %s <archivo_1> ", argv[0]);
      return -1;
   }

   strcpy(filename, argv[1]);

   if (!(f = fopen(filename, "r")))
   {
      return -1;
   }

   delivery = build_delivery(f);
   fprintf(stdout, "\n");
   delivery_run_plan(stdout, delivery, vertex_print, vertex_free);

   delivery_free(delivery);

   fclose(f);
   return 0;
}