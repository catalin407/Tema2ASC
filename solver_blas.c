/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/* 
 * Add your BLAS implementation here
 */

#include "cblas.h"

double* my_solver(int N, double *A, double *B) {
	double *temp1 = (double *)calloc(N*N, sizeof(double));
	double *temp2 = (double *)calloc(N*N, sizeof(double));
	double *unit_matrix = (double *)calloc(N*N, sizeof(double));
	int i;

	for (i = 0; i < N * N; i++) {
		temp1[i] = B[i];
	}

	for (i = 0; i < N; i++)
		unit_matrix[i * N + i] = 1.0;

	// B * A
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit,
			N, N, 1, A, N, temp1, N);

	//temp2 = B_trans * B
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans,
			N, N, N, 1, B, N, B, N, 0, temp2, N);

	//temp1  * A_trans
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit,
			N, N, 1, A, N, temp1, N);

	//temp1 + temp2
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
			N, N, N, 1, temp1, N, unit_matrix, N, 1, temp2, N);

	free(temp1);
	free(unit_matrix);
	return temp2;
}
