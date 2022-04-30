/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */

double* my_solver(int N, double *A, double *B) {
	double *A_trans = (double *)calloc(N*N, sizeof(double));
	double *B_trans = (double *)calloc(N*N, sizeof(double));
	double *tmp1 = (double *)calloc(N*N, sizeof(double));
	double *tmp2 = (double *)calloc(N*N, sizeof(double));
	double *tmp3 = (double *)calloc(N*N, sizeof(double));
	double *C = (double *)calloc(N*N, sizeof(double));
	double suma;

	int i, j, k;

	// A_Trans, B_trans
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++) {
			A_trans[j * N + i] = A[i * N + j];
			B_trans[j * N + i] = B[i * N + j];
		}

	// tmp1 = B * A
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++) {
			suma = 0.0;
			for (k = 0; k <= j; k++) {
					suma += B[i * N + k] * A[k * N + j];
			}
			tmp1[i * N + j] = suma;
		}
	// tmp2 = tmp1 * A_trans
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++) {
			suma = 0.0;
			for (k = j; k < N; k++) {
					suma += tmp1[i * N + k] * A_trans[k * N + j];
			}
			tmp2[i * N + j] = suma;
		}

	// tmp3 = B_trans * B
	for (i = 0; i< N; i++)
		for (j = 0; j < N; j++) {
			suma = 0.0;
			for (k = 0; k < N; k++)
				suma += B_trans[i * N + k] * B[k * N + j];
			tmp3[i * N + j] = suma;
		}
	// C = tmp2 + tmp3
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			C[i * N + j] = tmp2[i * N + j] + tmp3[i * N + j];

	free(A_trans);
	free(B_trans);
	free(tmp1);
	free(tmp2);
	free(tmp3);

	return C;
}
