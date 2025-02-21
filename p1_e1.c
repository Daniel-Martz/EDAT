#include "vertex.h"
#include <stdio.h>

int main()
{
    Vertex *v1 = NULL, *v2 = NULL, *v3 = NULL;
    int cmp_aux = 0;

    v1 = vertex_init();
    v2 = vertex_init();

    if (!v1 || !v2)
    {
        vertex_free(v1);
        vertex_free(v2);
        return 1;
    }

    if (vertex_setId(v1, 10) == ERROR)
    {
        vertex_free(v1);
        vertex_free(v2);
        return 0;
    }

    if (vertex_setTag(v1, "one") == ERROR)
    {
        vertex_free(v1);
        vertex_free(v2);
        return 0;
    }
    if (vertex_setState(v1, WHITE) == ERROR)
    {
        vertex_free(v1);
        vertex_free(v2);
        return 0;
    }
    if (vertex_setId(v2, 20) == ERROR)
    {
        vertex_free(v1);
        vertex_free(v2);
        return 0;
    }
    if (vertex_setTag(v2, "two") == ERROR)
    {
        vertex_free(v1);
        vertex_free(v2);
        return 0;
    }
    if (vertex_setState(v2, BLACK) == ERROR)
    {
        vertex_free(v1);
        vertex_free(v2);
        return 0;
    }

    vertex_print(stdout, v1);
    vertex_print(stdout, v2);
    printf("\n");

    cmp_aux = vertex_cmp(v1, v2);
    if (!(cmp_aux))
        printf("Equals? Yes");
    else
        printf("Equals? No");
    printf("\n");
    
    printf("Vertex 2 tag: %s", vertex_getTag(v2));
    printf("\n");

    v3 = vertex_copy(v1);

    printf("Vertex 3 id: %ld", vertex_getId(v3));
    printf("\n");

    vertex_print(stdout, v1);
    vertex_print(stdout, v3);
    printf("\n");

    cmp_aux = vertex_cmp(v1, v3);
    if (!(cmp_aux))
        printf("Equals? Yes");
    else
        printf("Equals? No");

    vertex_free(v1);
    vertex_free(v2);
    vertex_free(v3);

    return 0;
}