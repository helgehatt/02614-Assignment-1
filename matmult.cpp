
extern "C" {
#include <cblas.h>

void matmult_nat(int m,int n,int k,double **A,double **B,double **C);
void matmult_lib(int m,int n,int k,double **A,double **B,double **C);

void matmult_mkn(int m,int n,int k,double **A,double **B,double **C);
void matmult_mnk(int m,int n,int k,double **A,double **B,double **C);
void matmult_kmn(int m,int n,int k,double **A,double **B,double **C);
void matmult_knm(int m,int n,int k,double **A,double **B,double **C);
void matmult_nmk(int m,int n,int k,double **A,double **B,double **C);
void matmult_nkm(int m,int n,int k,double **A,double **B,double **C);

void matmult_blk(int m,int n,int k,double **A,double **B,double **C, int bs);
}

#define FOR_i_TO_m for (i = 0; i < m; i++)
#define FOR_j_TO_n for (j = 0; j < n; j++)
#define FOR_l_TO_k for (l = 0; l < k; l++)

#define RESET_C FOR_i_TO_m FOR_j_TO_n C[i][j] = 0;

#define MIN(a,b) ((a) < (b) ? a : b)

void matmult_nat(int m,int n,int k,double **A,double **B,double **C)
{
    int i, j, l;
    
    RESET_C

    FOR_i_TO_m
        FOR_j_TO_n
            FOR_l_TO_k
                C[i][j] += A[i][l] * B[l][j];
}

void matmult_lib(int m,int n,int k,double **A,double **B,double **C)
{
    cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,m,n,k,1,A[0],k,B[0],n,0,C[0],n);
}

void matmult_mkn(int m,int n,int k,double **A,double **B,double **C)
{
    int i, j, l;
    
    RESET_C

    FOR_i_TO_m
        FOR_l_TO_k
            FOR_j_TO_n
                C[i][j] += A[i][l] * B[l][j];
}

void matmult_mnk(int m,int n,int k,double **A,double **B,double **C)
{
    matmult_nat(m, n, k, A, B, C);
}

void matmult_kmn(int m,int n,int k,double **A,double **B,double **C)
{    
    int i, j, l;
    
    RESET_C

    FOR_l_TO_k
        FOR_i_TO_m
            FOR_j_TO_n
                C[i][j] += A[i][l] * B[l][j];
}
void matmult_knm(int m,int n,int k,double **A,double **B,double **C)
{
    int i, j, l;
    
    RESET_C

    FOR_l_TO_k
        FOR_j_TO_n
            FOR_i_TO_m
                C[i][j] += A[i][l] * B[l][j];
}

void matmult_nmk(int m,int n,int k,double **A,double **B,double **C)
{
    int i, j, l;
    
    RESET_C

    FOR_j_TO_n
        FOR_i_TO_m
            FOR_l_TO_k
                C[i][j] += A[i][l] * B[l][j];
}

void matmult_nkm(int m,int n,int k,double **A,double **B,double **C)
{
    int i, j, l;
    
    RESET_C

    FOR_j_TO_n
        FOR_l_TO_k
            FOR_i_TO_m
                C[i][j] += A[i][l] * B[l][j];
}

void matmult_blk(int m,int n,int k,double **A,double **B,double **C, int bs)
{
    int I, J, L, i, j, l, sum, limi, limj, liml;

    RESET_C

    for (I = 0; I < m; I+=bs)
	{
	limi = MIN(I+bs,m);
        for (i = I; i < limi; i++)
            for (L = 0; L < k; L+=bs)
	    	{
	   	liml = MIN(L+bs,k);
            	for (l = L; l < liml; l++)
            	    for (J = 0; J < n; J+=bs)
			{
			limj = MIN(J+bs,n);
                	for (j = J; j < limj; j++)
                            C[i][j] += A[i][l] * B[l][j];
			};
	     	};
		
	};
}