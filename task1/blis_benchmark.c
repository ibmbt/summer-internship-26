#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blis.h"

void randomize_matrix(double* matrix, dim_t N) {
    for (size_t i = 0; i < (size_t)N * N; i++) {
        matrix[i] = (double)rand() / RAND_MAX;
    }
}

int main() {
    printf("--- BLIS GEMM Benchmark (2k to 18k) ---\n");
    printf("%-10s %-15s %-15s\n", "Size (N)", "Time (seconds)", "Performance (GFLOPS)");
    printf("----------------------------------------------\n");

    double alpha = 1.0;
    double beta = 0.0;
    struct timespec t_start, t_end;

    for (dim_t N = 2000; N <= 18000; N += 2000) {

        size_t num_elements = (size_t)N * N;

        double* A = (double*)malloc(num_elements * sizeof(double));
        double* B = (double*)malloc(num_elements * sizeof(double));
        double* C = (double*)malloc(num_elements * sizeof(double));

        if (!A || !B || !C) {
            printf("FATAL: Out of RAM at N=%d\n", (int)N);
            return 1;
        }

        randomize_matrix(A, N);
        randomize_matrix(B, N);

        inc_t rs = N;
        inc_t cs = 1;

        clock_gettime(CLOCK_MONOTONIC, &t_start);

        bli_dgemm(BLIS_NO_TRANSPOSE, BLIS_NO_TRANSPOSE,
            N, N, N,
            &alpha,
            A, rs, cs,
            B, rs, cs,
            &beta,
            C, rs, cs);

        clock_gettime(CLOCK_MONOTONIC, &t_end);

        double time_taken = (t_end.tv_sec - t_start.tv_sec) +
            (t_end.tv_nsec - t_start.tv_nsec) / 1.0e9;

        double flops = 2.0 * N * N * N;
        double gflops = (flops / time_taken) / 1.0e9;

        printf("%-10d %-15.4f %-15.2f\n", (int)N, time_taken, gflops);

        free(A);
        free(B);
        free(C);
    }

    return 0;
}