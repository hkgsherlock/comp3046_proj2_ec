#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "vector.h"
#include "matrix.h"
#include "gaussian.h"
#include "gaussian_omp.h"
#include "gaussian_validate.h"

int main() {
    int n, thread_count;

    clock_t serialStart, serialEnd;
    double ompStart, ompEnd;

    do {
        printf("Size of vector b and side length of matrix A: ");
        scanf("%d", &n);
    } while (n < 2);

    do {
        printf("Number of threads: ");
        scanf("%d", &thread_count);
    } while (thread_count < 2);

    printf("\n");
    printf("\n");
    printf("\n");

//    srand((unsigned int) time(NULL));
//    int n = rand() % 5 + 3;

    double *A = (double *) malloc(n * n * sizeof(double));
    double *AA = (double *) malloc(n * n * sizeof(double));
    double *b = (double *) malloc(n * sizeof(double));
    double *bb = (double *) malloc(n * sizeof(double));
    double *x = (double *) malloc(n * sizeof(double));

    Mat_Init(n, n, A);
    Vec_Init(n, b);
    if (n <= 20) {
        printf("[Init] Matrix A: \n");
        Mat_Show_p(n, n, A, 0);
        printf("\n");
        printf("[Init] Vector b: \n");
        Vec_Show_p(n, b, 0);
    }

    printf("\n");
    printf("==================================================\n");
    printf("\n");

    Mat_Clone(n, n, A, AA);
    Vec_Clone(n, b, bb);

    serialStart = clock();
    Gaussian_getX(n, A, b, x);
    serialEnd = clock();
    if (n <= 20) {
        printf("[Single] Vector x: \n");
        Vec_Show(n, x);
        printf("\n");
    }
    printf("[Single] Elapse: %lf milliseconds\n", ((float)(serialEnd - serialStart) / CLOCKS_PER_SEC) * 1000);
    printf("\n");
    printf("[Single] Error: \n");
    Gaussian_assert_validateX(n, AA, bb, x, 0.000001);

    printf("\n");
    printf("==================================================\n");
    printf("\n");

    Mat_Clone(n, n, AA, A);
    Vec_Clone(n, bb, b);

    ompStart = omp_get_wtime();
    Gaussian_getX_omp(n, A, b, x, thread_count);
    ompEnd = omp_get_wtime();
    if (n <= 20) {
        printf("[OMP] Vector x: \n");
        Vec_Show(n, x);
        printf("\n");
    }
    printf("[OMP] Elapse: %lf milliseconds\n", (ompEnd - ompStart) * 1000);
    printf("\n");
    printf("[OMP] Error: \n");
    Gaussian_assert_validateX(n, AA, bb, x, 0.000001);

    printf("\n");

    free(x);
    free(bb);
    free(b);
    free(AA);
    free(A);

    return 0;
}