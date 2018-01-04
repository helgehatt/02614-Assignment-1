#pragma once

void matrix_add         (int m, int n,          double **A, double **B, double **C);
void matrix_vector_mul  (int m, int n,          double **A, double  *B, double  *C);
void matrix_matrix_mul  (int m, int k, int n,   double **A, double **B, double **C);
