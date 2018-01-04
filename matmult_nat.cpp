
extern "C" {
#include <cblas.h>
}

#define FOR_i_TO_m for (i = 0; i < m; i++)
#define FOR_j_TO_n for (j = 0; j < n; j++)
#define FOR_l_TO_k for (l = 0; l < k; l++)

#define RESET_C FOR_i_TO_m FOR_j_TO_n C[i][j] = 0;

#define MIN(a,b) ((a) < (b) ? a : b)

void matmult_nat(int m,int n,int k,double **A,double **B,double **C)
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