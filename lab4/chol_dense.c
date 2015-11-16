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


int
chol(double *A, unsigned int n)
{
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

int
speed_chol(double *A, unsigned int n)
{

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


int
main()
{

    double *A;
    int i, j, n, ret, result;
    char matrix_file[30];
    double start_time, end_time;

    n = 10;
    sprintf(matrix_file, "input/matrix_%dx%d.txt", n, n);

    A = load_matrix(matrix_file, n);

//    A[IDX(0, 0, n)] = 4.0;   A[IDX(0, 1, n)] = 12.0;  A[IDX(0, 2, n)] = -16.0;
//    A[IDX(1, 0, n)] = 12.0;  A[IDX(1, 1, n)] = 37.0;  A[IDX(1, 2, n)] = -43.0;
//    A[IDX(2, 0, n)] = -16.0; A[IDX(2, 1, n)] = -43.0; A[IDX(2, 2, n)] = 98.0;

    start_time = dclock();
    result = speed_chol(A, n);
//    result = chol(A, n);
    end_time = dclock();

    if (result != 0) {
        fprintf(stderr, "Error: matrix is either not symmetric or not positive definite.\n");
    } else {
        fprintf(stdout, "Execution time: %le\n", end_time - start_time);
//        fprintf(stdout, "Tri(L) = \n");
//        for (i = 0; i < n; i++) {
//            for (j = 0; j <= i; j++)
//                printf("%2.8lf\t", A[IDX(i, j, n)]);
//            printf("\n");
//        }
    }

    free(A);
    return 0;
}

