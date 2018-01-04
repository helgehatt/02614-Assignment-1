#include "stdafx.h"
#include <time.h>

extern "C" {
#include <cblas.h>
}

#define NREPEAT 100
#define delta_t(a,b) (1e3 * (b - a) / CLOCKS_PER_SEC)

// Examples from http://mathinsight.org/matrix_vector_multiplication

void test_correctness_matrix_add(void)
{
    printf("test_correctness_matrix_add\n");

    const int m = 2, n = 3;

    double **A = malloc_matrix(m, n);
    double **B = malloc_matrix(m, n);
    double **C = malloc_matrix(m, n);

    int i, j;

    FOR_i_TO_m
        FOR_j_TO_n
        {
            A[i][j] = 1;
            B[i][j] = 2;
        }

    matrix_add(m, n, A, B, C);

    FOR_i_TO_m
        FOR_j_TO_n
            assert(C[i][j] == 3);
}

void test_correctness_matrix_vector_mul(void)
{
    printf("test_correctness_matrix_vector_mul\n");

    const int m = 2, n = 3;

    double **A = malloc_matrix(m, n);
    double  *B = malloc_vector(n);
    double  *C = malloc_vector(n);

    // double A[m][n] = {
    //     {1, -1, 2},
    //     {0, -3, 1}
    // };

    A[0][0] = 1; A[0][1] = -1; A[0][2] = 2;
    A[1][0] = 0; A[1][1] = -3; A[1][2] = 1;

    // double B[n] = {2, 1, 0};

    B[0] = 2; B[1] = 1; B[2] = 0;

    double R[m] = {1, -3};

    matrix_vector_mul(m, n, A, B, C);

    int i;

    FOR_i_TO_m
        assert(C[i] == R[i]);
}

void test_correctness_matrix_matrix_mul(void)
{
    printf("test_correctness_matrix_matrix_mul\n");

    const int m = 2, k = 3, n = 2;

    double **A = malloc_matrix(m, k);
    double **B = malloc_matrix(k, n);
    double **C = malloc_matrix(m, n);

    // double A[m][k] = {
    //     { 0,  4, -2},
    //     {-4, -3,  0}
    // };

    A[0][0] =  0; A[0][1] =  4; A[0][2] = -2;
    A[1][0] = -4; A[1][1] = -3; A[1][2] =  0;

    // double B[k][n] = {
    //     {0,  1},
    //     {1, -1},
    //     {2,  3}
    // };

    B[0][0] = 0; B[0][1] =  1;
    B[1][0] = 1; B[1][1] = -1;
    B[2][0] = 2; B[2][1] =  3;

    double R[m][n] = {
        { 0, -10},
        {-3,  -1}
    };

    matrix_matrix_mul(m, k, n, A, B, C);

    int i, j;

    FOR_i_TO_m
        FOR_j_TO_n
            assert(C[i][j] == R[i][j]);
}

void test_runtime_matrix_add(void)
{
    printf("test_runtime_matrix_add\n");

    int i, m, n, N = NREPEAT, t1, t2;
    double **A, **B, **C, tcpu1;

    for (m = 200; m <= 3500; m += 300)
    {
        n = m + 25;

		A = malloc_matrix(m, n);
		B = malloc_matrix(m, n);
		C = malloc_matrix(m, n);

		if (A == NULL || B == NULL | C == NULL) {
			fprintf(stderr, "Memory allocation error...\n");
			exit(EXIT_FAILURE);
		}

        init_matrix(m, n, A);
        init_matrix(m, n, B);

		t1 = clock();
		for (i = 0; i < N; i++)
			matrix_add(m, n, A, B, C);
		t2 = clock();
		tcpu1 = delta_t(t1, t2) / N;

		printf("%4d %4d %8.3f\n", m, n, tcpu1);

        dealloc_matrix(A);
        dealloc_matrix(B);
        dealloc_matrix(C);
    }
}

void test_runtime_matrix_vector_mul(void)
{
    printf("test_runtime_matrix_vector_mul\n");

    int i, m, n, N = NREPEAT, t1, t2;
    double **A, *B, *C, tcpu1;

    for (m = 200; m <= 3500; m += 300)
    {
        n = m + 25;

		A = malloc_matrix(m, n);
		B = malloc_vector(n);
		C = malloc_vector(m);

		if (A == NULL || B == NULL | C == NULL) {
			fprintf(stderr, "Memory allocation error...\n");
			exit(EXIT_FAILURE);
		}

        init_matrix(m, n, A);
        init_vector(n, B);

		t1 = clock();
		for (i = 0; i < N; i++)
			matrix_vector_mul(m, n, A, B, C);
		t2 = clock();
		tcpu1 = delta_t(t1, t2) / N;

		printf("%4d %4d %8.3f\n", m, n, tcpu1);

        dealloc_matrix(A);
        dealloc_vector(B);
        dealloc_vector(C);
    }
}

void test_runtime_matrix_matrix_mul(void)
{
    printf("test_runtime_matrix_matrix_mul\n");

    int i, m, k, n, N = NREPEAT, t1, t2;
    double **A, **B, **C, tcpu1;

    for (m = 20; m <= 350; m += 30)
    {
        k = m - 5;
        n = m + 5;

		A = malloc_matrix(m, k);
		B = malloc_matrix(k, n);
		C = malloc_matrix(m, n);

		if (A == NULL || B == NULL | C == NULL) {
			fprintf(stderr, "Memory allocation error...\n");
			exit(EXIT_FAILURE);
		}

        init_matrix(m, k, A);
        init_matrix(k, n, B);

		t1 = clock();
		for (i = 0; i < N; i++)
			matrix_matrix_mul(m, k, n, A, B, C);
		t2 = clock();
		tcpu1 = delta_t(t1, t2) / N;

		printf("%4d %4d %4d %8.3f\n", m, k, n, tcpu1);

        dealloc_matrix(A);
        dealloc_matrix(B);
        dealloc_matrix(C);
    }
}

void test_runtime_matrix_matrix_mul_cblas(void)
{
    printf("test_runtime_matrix_matrix_mul_cblas\n");

    int i, m, k, n, N = NREPEAT, t1, t2;
    double **A, **B, **C, tcpu1, alpha = 1, beta = 0;

    for (m = 20; m <= 350; m += 30)
    {
        k = m - 5;
        n = m + 5;

        // const double *A, *B;
		A = malloc_matrix(m, k);
		B = malloc_matrix(k, n);
		C = malloc_matrix(m, n);

		if (A == NULL || B == NULL | C == NULL) {
			fprintf(stderr, "Memory allocation error...\n");
			exit(EXIT_FAILURE);
		}

        init_matrix(m, k, A);
        init_matrix(k, n, B);

		t1 = clock();
		for (i = 0; i < N; i++)
            cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,m,n,k,alpha,&A[0][0],k,&B[0][0],n,beta,&C[0][0],n);
		t2 = clock();
		tcpu1 = delta_t(t1, t2) / N;

		printf("%4d %4d %4d %8.3f\n", m, k, n, tcpu1);

        dealloc_matrix(A);
        dealloc_matrix(B);
        dealloc_matrix(C);
    }
}