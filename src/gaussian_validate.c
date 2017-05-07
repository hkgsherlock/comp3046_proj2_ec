#include "gaussian_validate.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "matrix.h"
#include "vector.h"
#include "printf_if.h"

void Gaussian_validateX(int n, double *A, double *b, double *x, double *bb, double *err) {
    Mat_Xv(n, n, A, bb, x);

    int i;
    for (i = 0; i < n; i++) {
        err[i] = fabs(b[i] - bb[i]);
    }
}

void Gaussian_show_validateX(int n, double *A, double *b, double *x) {
    double *err = (double *) malloc(n * sizeof(double));
    double *bb = (double *) malloc(n * sizeof(double));
    Gaussian_validateX(n, A, b, x, bb, err);
    Vec_Show(n, err);
    free(bb);
    free(err);
}

int Gaussian_assert_validateX(int n, double *A, double *b, double *x, double err_rate, bool show) {
    double *err = (double *) malloc(n * sizeof(double));
    double *bb = (double *) malloc(n * sizeof(double));
    Gaussian_validateX(n, A, b, x, bb, err);
    int i;
    int err_occur = 0;
    for (i = 0; i < n; i++) {
        if (err[i] > err_rate) {
            if (n <= 20) {
                printf_if(show, "Assertion failed! \nExpected: %lf\nActual: %lf\nError: %lf\n", b[i], bb[i], err[i]);
            }
            err_occur++;
        }
    }
    if (err_occur == 0) {
        printf_if(show, "not found\n");
    } else {
        printf_if(show, "err count: %d\n", err_occur);
    }
    free(bb);
    free(err);

    return err_occur;
}