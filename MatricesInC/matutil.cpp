#include "stdafx.h"

#include "matutil.h"

double *malloc_vector(int m)
{
    double *A = new double[m];

    return A;
}

double **malloc_matrix(int m, int n)
{
    double **A = new double *[m];

    A[0] = new double[n*m];
    
    int i;

    FOR_i_TO_m
	    A[i] = A[0] + i * n;

    return A;
}

void dealloc_vector(double *A)
{
    delete [] A;
}

void dealloc_matrix(double **A)
{
    delete [] A;
}

void print_vector(int m, double *A)
{
    int i;

    FOR_i_TO_m
        printf("%f ", A[i]);

    printf("\n");
}

void print_matrix(int m, int n, double **A)
{
    int i;

    FOR_i_TO_m
        print_vector(n, A[i]);
}


void init_vector (int m, double *A) 
{
    int i;

    FOR_i_TO_m
        A[i] = 2;
}

void init_matrix(int m, int n, double **A)
{
    int i;

    FOR_i_TO_m
        init_vector(n, A[i]);
}


// double  *
// malloc_1d(int m)
// {
//     if (m <= 0)
// 	    return NULL;

//     double *A = (double *)malloc(m * sizeof(double));

//     return A;
// }

// double **
// malloc_2d(int m, int n)
// {
//     int i;

//     if (m <= 0 || n <= 0)
// 	    return NULL;

//     double **A = (double **)malloc(m * sizeof(double *));
//     if (A == NULL)
// 	    return NULL;

//     A[0] = (double *)malloc(m*n*sizeof(double));
//     if (A[0] == NULL) {
// 	    free(A);
// 	    return NULL;
//     }
//     for (i = 1; i < m; i++)
// 	    A[i] = A[0] + i * n;

//     return A;
// }

// void
// free_2d(double **A) {
//     free(A[0]);
//     free(A);
// }