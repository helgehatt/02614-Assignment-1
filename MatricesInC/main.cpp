#include "stdafx.h"

void test_correctness(void)
{
    test_correctness_matrix_add();
    test_correctness_matrix_vector_mul();
    test_correctness_matrix_matrix_mul();
}

void test_runtime(void)
{
    test_runtime_matrix_add();
    test_runtime_matrix_vector_mul();
    test_runtime_matrix_matrix_mul();
    test_runtime_matrix_matrix_mul_cblas();
}

int main(int argc, char *argv[]) 
{
    // test_correctness();
    // test_runtime();
    test_runtime_matrix_matrix_mul_cblas();
    return 0;
}