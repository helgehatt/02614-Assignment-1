#include "stdafx.h"

void matrix_add(int m, int n, double **A, double **B, double **C)
{
    int i, j;

    FOR_i_TO_m 
        FOR_j_TO_n
            C[i][j] = A[i][j] + B[i][j];
}

void matrix_vector_mul(int m, int n, double **A, double *B, double *C)
{
    int i, j;

    FOR_i_TO_m
        C[i] = 0;

    FOR_i_TO_m
        FOR_j_TO_n
            C[i] += A[i][j] * B[j];
}

void matrix_matrix_mul(int m, int k, int n, double **A, double **B, double **C)
{
    int i, j, l;
    
    FOR_i_TO_m
        FOR_j_TO_n
            C[i][j] = 0;

    FOR_i_TO_m
        FOR_j_TO_n
            FOR_l_TO_k
                C[i][j] += A[i][l] * B[l][j];
}