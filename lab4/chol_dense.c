//
// Created by piotr on 09.11.15.
//

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chol_dense.h"
#include "clock.h"


#define IDX(i, j, n) (((j)+ (i)*(n)))


int chol(double *A, unsigned int n);
int speed_chol(double *A, unsigned int n);
int assert_matrix_equality(double *A, double *B, int n);
double* load_matrix(char* filename, int n);


int main(){

    double *A, *B;
    int i, j, n, ret, result1, result2;
    char matrix_file[30];
    double start_time1, end_time1, start_time2, end_time2;

    n = 10;
    sprintf(matrix_file, "input/matrix_%dx%d.txt", n, n);

    A = load_matrix(matrix_file, n);
    B = load_matrix(matrix_file, n);

    start_time1 = dclock();
    result1 = chol(A, n);
    end_time1 = dclock();

    start_time2 = dclock();
    result2 = speed_chol(B, n);
    end_time2 = dclock();

    if (assert_matrix_equality(A, B, n)){
        printf("Algorithms differ in results!\n");
        free(A);
        free(B);
        exit(1);
    }

    if (result1 != 0) {
        fprintf(stderr, "Error: matrix is either not symmetric or not positive definite.\n");
    } else
        fprintf(stdout, "\nStandard algorithm execution time:\t %le\n", end_time1 - start_time1);

    if (result2 != 0) {
        fprintf(stderr, "Error: matrix is either not symmetric or not positive definite.\n");
    } else
        fprintf(stdout, "Optimized algorithm execution time:\t %le\n\n", end_time2 - start_time2);


    free(A);
    free(B);
    return 0;

}


int chol(double *A, unsigned int n){

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


int speed_chol(double *A, unsigned int n){

    register unsigned int i;
    register unsigned int j;
    register unsigned int k;

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


int assert_matrix_equality(double *A, double *B, int n){
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j <= i; j++)
            if (A[IDX(i, j, n)] != B[IDX(i, j, n)])
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