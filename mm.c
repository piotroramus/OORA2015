//
// Created by piotr on 08.11.15.
//

#include "mm.h"

int mm1(double first[][SIZE], double second[][SIZE], double multiply[][SIZE])
{
    int i,j,k;
    double sum = 0;
    for (i = 0; i < SIZE; i++) { //rows in multiply
        for (j = 0; j < SIZE; j++) { //columns in multiply
            for (k = 0; k < SIZE; k++) { //columns in first and rows in second
                sum = sum + first[i][k]*second[k][j];
            }
            multiply[i][j] = sum;
            sum = 0;
        }
    }
    return 0;
}