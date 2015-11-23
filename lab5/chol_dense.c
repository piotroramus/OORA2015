//
// Created by piotr on 09.11.15.
//

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>

#include "chol_dense.h"
#include "papi_template.h"
#include "clock.h"


#define IDX(i, j, n) (((j)+ (i)*(n)))

//this way of IDX seems to be much slower than previous (without using SIMD instructions)
//#define IDX(i, j, n) ( (i) * ((i) + 1) / 2 + (j) )


int chol(double *A, int n);
int speed_chol(double *A, int n);
int simd_chol(double *A, int n);
int assert_matrix_equality(double *A, double *B, int n);
double* load_matrix(char* filename, int n);


int main(){

    //processor specs:
    // http://www.cpu-world.com/CPUs/Core_i7/Intel-Core%20i7-3630QM%20Mobile%20processor.html

    // useful article
    // http://www.codeproject.com/Articles/874396/Crunching-Numbers-with-AVX-and-AVX

    double *A, *B, *C;
    int i, j, n, ret, result;
    char matrix_file[30];
    double start_time, end_time, time;
    double gflops_prefix, gflops;

    n = 1000;
    gflops_prefix = (n * n * n * 1.0e-6) / 3.0;
    sprintf(matrix_file, "input/matrix_%dx%d.txt", n, n);

    A = load_matrix(matrix_file, n);
    B = load_matrix(matrix_file, n);
    C = load_matrix(matrix_file, n);

    fprintf(stdout, "\n====================================================\n");
    fprintf(stdout, "\nMatrix size: %d\n\n", n);

    fprintf(stdout, "Standard algorithm\n");
    start_time = dclock();
    result = chol(A, n);
    end_time = dclock();

    if (result != 0) {
        fprintf(stderr, "Error: matrix is either not symmetric or not positive definite.\n");
        exit(2);
    } else {
        time = end_time - start_time;
        fprintf(stdout, "Execution time:\t\t\t\t %le\n", time);
        fprintf(stdout, "MFLOPS:\t\t\t\t\t %f\n", gflops_prefix / time);
    }


    int event_type;
    for (event_type = 0; event_type < 4; event_type++){
        A = load_matrix(matrix_file, n);
        measure(chol, A, n, event_type);
    }


    fprintf(stdout, "\nOptimized algorithm\n");
    start_time = dclock();
    result = speed_chol(B, n);
    end_time = dclock();

    if (result != 0) {
        fprintf(stderr, "Error: matrix is either not symmetric or not positive definite.\n");
        exit(2);
    } else {
        time = end_time - start_time;
        fprintf(stdout, "Execution time:\t\t\t\t %le\n", time);
        fprintf(stdout, "MFLOPS:\t\t\t\t\t %f\n", gflops_prefix / time);
    }

    for (event_type = 0; event_type < 4; event_type++){
        B = load_matrix(matrix_file, n);
        measure(speed_chol, B, n, event_type);
    }


    fprintf(stdout, "\nSIMD algorithm\n");
    start_time = dclock();
    result = simd_chol(C, n);
    end_time = dclock();

    if (result != 0) {
        fprintf(stderr, "Error: matrix is either not symmetric or not positive definite.\n");
        exit(2);
    } else {
        time = end_time - start_time;
        fprintf(stdout, "Execution time:\t\t\t\t %le\n", time);
        fprintf(stdout, "MFLOPS:\t\t\t\t\t %f\n", gflops_prefix / time);
    }

    for (event_type = 0; event_type < 4; event_type++){
        C = load_matrix(matrix_file, n);
        measure(simd_chol, C, n, event_type);
    }


    fprintf(stdout, "\n");
    fprintf(stdout, "====================================================\n");

    if (assert_matrix_equality(A, C, n)){
        printf("Algorithms differ in results!\n");
        free(A);
        free(B);
        free(C);
        exit(1);
    }

    free(A);
    free(B);
    free(C);
    return 0;

}


int chol(double *A, int n){

    unsigned int i;
    unsigned int j;
    unsigned int k;

    for (j = 0; j < n; j++) {
        for (i = j; i < n; i++) {
            for (k = 0; k < j; ++k) {
                A[IDX(i, j, n)] -= A[IDX(i, k, n)] *
                                   A[IDX(j, k, n)];
            }
        }

        if (A[IDX(j, j, n)] < 0.0) {
            return (1);
        }

        A[IDX(j, j, n)] = sqrt(A[IDX(j, j, n)]);
        for (i = j + 1; i < n; i++)
            A[IDX(i, j, n)] /= A[IDX(j, j, n)];
    }

    return (0);
}


int speed_chol(double *A, int n){

    register unsigned int i;
    register unsigned int j;
    register unsigned int k;
    register int local_size = n;

    for (j = 0; j < local_size; j++) {
        for (i = j; i < local_size; i++) {
            register double Aij = A[IDX(i, j, local_size)];
            if (j > 8)
                for (k = 0; k < j;) {
                    if (k < j - 8){
                        Aij -= A[IDX(i, k, local_size)] * A[IDX(j, k, local_size)];
                        Aij -= A[IDX(i, k + 1, local_size)] * A[IDX(j, k + 1, local_size)];
                        Aij -= A[IDX(i, k + 2, local_size)] * A[IDX(j, k + 2, local_size)];
                        Aij -= A[IDX(i, k + 3, local_size)] * A[IDX(j, k + 3, local_size)];
                        Aij -= A[IDX(i, k + 4, local_size)] * A[IDX(j, k + 4, local_size)];
                        Aij -= A[IDX(i, k + 5, local_size)] * A[IDX(j, k + 5, local_size)];
                        Aij -= A[IDX(i, k + 6, local_size)] * A[IDX(j, k + 6, local_size)];
                        Aij -= A[IDX(i, k + 7, local_size)] * A[IDX(j, k + 7, local_size)];
                        k = k + 8;
                    } else {
                        Aij -= A[IDX(i, k, local_size)] * A[IDX(j, k, local_size)];
                        k++;
                    }
            }
            // i <= 8
            else for (k = 0; k < j; ++k)
                    Aij -= A[IDX(i, k, local_size)] * A[IDX(j, k, local_size)];
            A[IDX(i, j, local_size)] = Aij;
        }

        if (A[IDX(j, j, local_size)] < 0.0) {
            return (1);
        }

        A[IDX(j, j, local_size)] = sqrt(A[IDX(j, j, local_size)]);
        register double Ajj = A[IDX(j, j, n)];
        for (i = j + 1; i < local_size;){

            if (i < local_size - 8){
                A[IDX(i, j, local_size)] /= Ajj;
                A[IDX(i + 1, j, local_size)] /= Ajj;
                A[IDX(i + 2, j, local_size)] /= Ajj;
                A[IDX(i + 3, j, local_size)] /= Ajj;
                A[IDX(i + 4, j, local_size)] /= Ajj;
                A[IDX(i + 5, j, local_size)] /= Ajj;
                A[IDX(i + 6, j, local_size)] /= Ajj;
                A[IDX(i + 7, j, local_size)] /= Ajj;
                i += 8;
            } else {
                A[IDX(i, j, local_size)] /= Ajj;
                i++;
            }
        }
    }

    return (0);
}


int simd_chol(double *A, int n){

    register  int i;
    register  int j;
    register  int k;
    register  int local_size = n;
    register __m256d v1, v2, v3, v4, mul1, mul2, sum;

    for (j = 0; j < local_size; j++) {
        for (i = j; i < local_size; i++) {
            register double Aij = A[IDX(i, j, local_size)];
            if (j > 8)
                for (k = 0; k < j;) {
                    if (k < j - 8){

                        v1 = _mm256_loadu_pd(A+IDX(i, k, local_size));
                        v2 = _mm256_loadu_pd(A+IDX(j, k, local_size));
                        mul1 = _mm256_mul_pd(v1, v2);

                        v3 = _mm256_loadu_pd(A+IDX(i, k + 4, local_size));
                        v4 = _mm256_loadu_pd(A+IDX(j, k + 4, local_size));

                        mul2 = _mm256_mul_pd(v3, v4);

                        sum = _mm256_add_pd(mul1, mul2);
                        Aij -= (sum[3] + sum[2] + sum[1] + sum[0]);

                        k = k + 8;
                    } else {
                        Aij -= A[IDX(i, k, local_size)] * A[IDX(j, k, local_size)];
                        k++;
                    }
                }
                // i <= 8
            else for (k = 0; k < j; ++k)
                    Aij -= A[IDX(i, k, local_size)] * A[IDX(j, k, local_size)];
            A[IDX(i, j, local_size)] = Aij;
        }

        if (A[IDX(j, j, local_size)] < 0.0) {
            return (1);
        }

        A[IDX(j, j, local_size)] = sqrt(A[IDX(j, j, local_size)]);
        register double Ajj = A[IDX(j, j, n)];
        for (i = j + 1; i < local_size;){

            if (i < local_size - 8){
                A[IDX(i, j, local_size)] /= Ajj;
                A[IDX(i + 1, j, local_size)] /= Ajj;
                A[IDX(i + 2, j, local_size)] /= Ajj;
                A[IDX(i + 3, j, local_size)] /= Ajj;
                A[IDX(i + 4, j, local_size)] /= Ajj;
                A[IDX(i + 5, j, local_size)] /= Ajj;
                A[IDX(i + 6, j, local_size)] /= Ajj;
                A[IDX(i + 7, j, local_size)] /= Ajj;
                i += 8;
            } else {
                A[IDX(i, j, local_size)] /= Ajj;
                i++;
            }
        }
    }

    return (0);
}


int assert_matrix_equality(double *A, double *B, int n){
    int i, j;
    double epsilon = 0.0001;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (fabs(A[IDX(i, j, n)] - B[IDX(i, j, n)]) > epsilon)
                return 1;
    return 0;
}


double* load_matrix(char* filename, int n){

    char *line = NULL;
    char *token = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *fp;
    double *A;
    char newline[2] = "\n";
    int i = 0;
    int j = 0;


    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Cannot open input file\n");
        exit(1);
    }


    A = calloc(n*n, sizeof(double));
    assert(A != NULL);

    while ((read = getline(&line, &len, fp)) != -1)
        while ((token = strsep(&line, ",")) != NULL)
            if (strcmp(token, newline) != 0){
                A[IDX(i, j, n)] = atof(token);
                j++;
                if (j == n){
                    j = 0;
                    i++;
                }
            }

    fclose(fp);
    if (line)
        free(line);

    return A;
}