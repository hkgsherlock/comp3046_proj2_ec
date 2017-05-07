#include "gaussian.h"
#include <stdlib.h>

void Gaussian_Elimination(int n, double *A, double *b, double *y) {
    int i, j, k;

    for (k = 0; k < n; k++) {
        for (j = k + 1; j < n; j++) {
            A[k * n + j] = A[k * n + j] / A[k * n + k];
        }
        y[k] = b[k] / A[k * n + k];
        A[k * n + k] = 1;
        for (i = k + 1; i < n; i++) {
            for (j = k + 1; j < n; j++) {
                A[i * n + j] = A[i * n + j] - A[i * n + k] * A[k * n + j];
            }
            b[i] = b[i] - A[i * n + k] * y[k];
            A[i * n + k] = 0;
        }
    }
}

void Back_Substitution(int n, double *U, double *x, double *y) {
    int i, k;
    for (k = n - 1; k > -1; k--) {
        x[k] = y[k];
        for (i = k - 1; i > -1; i--) {
            y[i] = y[i] - x[k] * U[i * n + k];
        }
    }
}

void Gaussian_getX(int n, double *A, double *b, double *x) {
    double *y = (double *) malloc(n * sizeof(double));

    Gaussian_Elimination(n, A, b, y);
    Back_Substitution(n, A, x, y);

    free(y);
}