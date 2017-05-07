#ifndef VECTOR_H
#define VECTOR_H

#define BLOCKSIZE 64

void Vec_Init(int size, double *x);

void Vec_Show_p(int size, double *x, int precision);

void Vec_Show(int size, double *x);

void Vec_Clone(int size, double *src, double *dest);

#endif