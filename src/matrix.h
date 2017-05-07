/* matrix.h */
#ifndef MATRIX_H
#define MATRIX_H

#define BLOCKSIZE 64

void Mat_Init(int row, int col, double *X);

void Mat_Show_p(int row, int col, double *X, int precision);

void Mat_Show(int row, int col, double *X);

void Mat_Clone(int row, int col, double *Src, double *Dest);

void Mat_Xv(int row, int col, double *X, double *Y, double *v);

void Omp_Mat_Xv(int row, int col, double *X, double *Y, double *v, int thread_count);

#endif