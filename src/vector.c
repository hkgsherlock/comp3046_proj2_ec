/* implementation of vector operations */
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

/* initialize a vector x */
void Vec_Init(int size, double *x) {
    int i;

    for (i = 0; i < size; i++) {
        // x[i] = ( (double)rand() ) / ( (double)RAND_MAX);
        x[i] = (double) (rand() % 10 + 1);
    }
}

void Vec_Show_p(int size, double *x, int precision) {
    int i;

    printf("vector size = %d\n", size);
    for (i = 0; i < size; i++) {
        if (precision < 0) {
            printf("%lf ", x[i]);
        } else {
            printf("%.*f ", precision, x[i]);
        }
    }
    printf("\n");
}

void Vec_Show(int size, double *x) {
    Vec_Show_p(size, x, -1);
}

void Vec_Clone(int size, double *src, double *dest) {
    int i;
    for (i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}