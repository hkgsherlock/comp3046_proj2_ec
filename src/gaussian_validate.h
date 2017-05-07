#ifndef GAUSSIAN_VALIDATE_H
#define GAUSSIAN_VALIDATE_H

#include <stdbool.h>

void Gaussian_show_validateX(int n, double *A, double *b, double *x);

int Gaussian_assert_validateX(int n, double *A, double *b, double *x, double err_rate, bool show);

#endif //GAUSSIAN_VALIDATE_H
