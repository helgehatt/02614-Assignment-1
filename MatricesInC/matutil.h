
#pragma once

double **malloc_matrix(int m, int n);
double *malloc_vector(int m);

void dealloc_matrix(double **A);
void dealloc_vector(double *A);

void print_vector(int m, double *A);
void print_matrix(int m, int n, double **A);

void init_vector(int m, double *A);
void init_matrix(int m, int n, double **A);

double  *malloc_1d(int m);
double **malloc_2d(int m, int n);
void free_2d(double **A);