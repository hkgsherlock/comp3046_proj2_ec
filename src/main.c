#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <stdint.h>
#include <stdbool.h>

#include "vector.h"
#include "matrix.h"
#include "gaussian.h"
#include "gaussian_omp.h"
#include "gaussian_validate.h"
#include "printf_if.h"

int main(int argc, char *argv[]) {
    bool toJson = false;
    int n, thread_count;

    if (argc == 3) {
        n = (int) strtol(argv[1], (char **)NULL, 10);
        thread_count = (int) strtol(argv[2], (char **)NULL, 10);
        toJson = true;
    } else {
        do {
            printf("Size of vector b and side length of matrix A: ");
            scanf("%d", &n);
        } while (n < 2);

        do {
            printf("Number of threads: ");
            scanf("%d", &thread_count);
        } while (thread_count < 2);
    }

    clock_t serialStart, serialEnd;
    double ompStart, ompEnd;

    double perfSerial, perfOmp;
    int errSerial, errOmp;

    printf_if(!toJson, "\n");
    printf_if(!toJson, "\n");
    printf_if(!toJson, "\n");

//    printf_if(!toJson, "system size of double = %d\n", sizeof(double));
//    printf_if(!toJson, "n =  %d\n", n);
//    printf_if(!toJson, "SIZE_MAX =  %d\n", SIZE_MAX);
//
//    printf_if(!toJson, "\n");
//    printf_if(!toJson, "\n");
//    printf_if(!toJson, "\n");

//    srand((unsigned int) time(NULL));
//    int n = rand() % 5 + 3;

    double *A = (double *) malloc((unsigned long)(n * n * sizeof(double)));
    if (A == NULL) {
        printf_if(!toJson, "Failed to assign A.");
        exit(-1);
    }
    double *AA = (double *) malloc((unsigned long)(n * n * sizeof(double)));
    if (AA == NULL) {
        printf_if(!toJson, "Failed to assign AA.");
        exit(-1);
    }
    double *b = (double *) malloc(n * sizeof(double));
    if (b == NULL) {
        printf_if(!toJson, "Failed to assign b.");
        exit(-1);
    }
    double *bb = (double *) malloc(n * sizeof(double));
    if (bb == NULL) {
        printf_if(!toJson, "Failed to assign bb.");
        exit(-1);
    }
    double *x = (double *) malloc(n * sizeof(double));
    if (x == NULL) {
        printf_if(!toJson, "Failed to assign x.");
        exit(-1);
    }

    Mat_Init(n, n, A);
    Vec_Init(n, b);
    if (n <= 20 && !toJson) {
        printf("[Init] Matrix A: \n");
        Mat_Show_p(n, n, A, 0);
        printf("\n");
        printf("[Init] Vector b: \n");
        Vec_Show_p(n, b, 0);
    }

    printf_if(!toJson, "\n");
    printf_if(!toJson, "==================================================\n");
    printf_if(!toJson, "\n");

    Mat_Clone(n, n, A, AA);
    Vec_Clone(n, b, bb);

    double *y1 = (double *) malloc(n * sizeof(double));
    serialStart = clock();
//    ompStart = omp_get_wtime();
    Gaussian_getX(n, A, b, y1, x);
    serialEnd = clock();
//    ompEnd = omp_get_wtime();
    perfSerial = ((float)(serialEnd - serialStart) / CLOCKS_PER_SEC) * 1000;
//    perfSerial = (ompEnd - ompStart) * 1000;
    free(y1);
    if (n <= 20 && !toJson) {
        printf("[Single] Vector x: \n");
        Vec_Show(n, x);
        printf("\n");
    }
    printf_if(!toJson, "[Single] Elapse: %lf milliseconds\n", perfSerial);
    printf_if(!toJson, "\n");
    printf_if(!toJson, "[Single] Error: \n");
    errSerial = Gaussian_assert_validateX(n, AA, bb, x, 0.000001, !toJson);

    printf_if(!toJson, "\n");
    printf_if(!toJson, "==================================================\n");
    printf_if(!toJson, "\n");

    Mat_Clone(n, n, AA, A);
    Vec_Clone(n, bb, b);

    double *y2 = (double *) malloc(n * sizeof(double));
    ompStart = omp_get_wtime();
    Gaussian_getX_omp(n, A, b, y2, x, thread_count);
    ompEnd = omp_get_wtime();
    perfOmp = (ompEnd - ompStart) * 1000;
    free(y2);
    if (n <= 20 && !toJson) {
        printf("[OMP] Vector x: \n");
        Vec_Show(n, x);
        printf("\n");
    }
    printf_if(!toJson, "[OMP] Elapse: %lf milliseconds\n", perfOmp);
    printf_if(!toJson, "\n");
    printf_if(!toJson, "[OMP] Error: \n");
    errOmp = Gaussian_assert_validateX(n, AA, bb, x, 0.000001, !toJson);

    printf_if(!toJson, "\n");

    free(x);
    free(bb);
    free(b);
    free(AA);
    free(A);

    printf_if(toJson, "{\"n\":%d,\"threads\":%d,"
            "\"perf\":{\"serial\":%lf,\"omp\":%lf},"
            "\"err\":{\"serial\":%d,\"omp\":%d}}",
              n, thread_count, perfSerial, perfOmp, errSerial, errOmp);

    return 0;
}