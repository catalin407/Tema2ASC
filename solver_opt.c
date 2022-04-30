/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */

double* my_solver(int N, double *A, double *B) {
	double *A_trans = (double *)malloc(N*N*sizeof(double));
	double *B_trans = (double *)malloc(N*N*sizeof(double));
	double *tmp1 = (double *)calloc(N*N, sizeof(double));
	double *tmp2 = (double *)calloc(N*N, sizeof(double));
	double *tmp3 = (double *)calloc(N*N, sizeof(double));
	double *C = (double *)malloc(N*N * sizeof(double));

	int i, j, k;

	// A_Trans, B_trans
	for (i = 0; i < N; i++) {
		register double *indexInitA_trans = &A_trans[i * N];
		register double *indexInitB_trans = &B_trans[i * N];
		for (j = 0; j < N; j++) {
			indexInitA_trans[j] = A[j * N +i];
			indexInitB_trans[j] = B[j * N + i];
		}
	}

	// tmp1 = B * A
	for (i = 0; i < N; i++) {
		register double *indexInitB = &B[i * N];
		register double *indexInitTmp1 = &tmp1[i * N];
		for (k = 0; k < N; k++) {
			register double iB = indexInitB[k];
			register double *iA = &A[k * N]; 
			for (j = k; j < N; j++) {
				indexInitTmp1[j] += iB * iA[j];
			}
		}
	}

	// tmp2 = tmp1 * A_trans
	for (i = 0; i < N; i++) {
		register double *indexInitTmp1 = &tmp1[i * N];
		register double *indexInitTmp2 = &tmp2[i * N];
		for (k = 0; k < N; k++) {
			register double iTmp1 = indexInitTmp1[k];
			register double *iA_trans = &A_trans[k * N];
			for (j = 0; j <= k; j++) {
				 indexInitTmp2[j] += iTmp1 * iA_trans[j];
			}
		}
	}

	free(A_trans);

	// tmp3 = B_trans * B
	for (i = 0; i< N; i++) {
		register double *indexInitB_trans = &B_trans[i * N];
		register double *indexInitTmp3 = &tmp3[i * N];
		for (k = 0; k < N; k++) {
			register double iB_trans = indexInitB_trans[k];

			register double *iB = &B[k * N];
			for (j = 0; j < N; j++) {
				indexInitTmp3[j] += iB_trans * iB[j];
			}
		}
	}

	free(B_trans);

	// tmp2 + tmp3
	for (i = 0; i < N; i++) {
		register double *indexInitTmp2 = &tmp2[i * N];
		register double *indexInitTmp3 = &tmp3[i * N];
		register double *indexInitC = &C[i * N];
		for (j = 0; j < N; j++) {
			indexInitC[j] = indexInitTmp2[j] + indexInitTmp3[j];
		}
	}

	free(tmp1);
	free(tmp2);
	free(tmp3);

	return C;
}
