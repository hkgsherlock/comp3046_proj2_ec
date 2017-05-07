#ifndef GAUSSIAN_VALIDATE_H
#define GAUSSIAN_VALIDATE_H

void Gaussian_show_validateX(int n, double *A, double *b, double *x);

void Gaussian_assert_validateX(int n, double *A, double *b, double *x, double err_rate);

#endif //GAUSSIAN_VALIDATE_H
