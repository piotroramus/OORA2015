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

int mm2(double first[][SIZE], double second[][SIZE], double multiply[][SIZE])
{
    register unsigned int i,j,k; //<- OPT 1
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

int mm3(double first[][SIZE], double second[][SIZE], double multiply[][SIZE])
{
    register unsigned int i,j,k; //<- OPT 1
    register unsigned int local_size=SIZE; //<- OPT 2
    double sum = 0;
    for (i = 0; i < local_size; i++) { //rows in multiply
        for (j = 0; j < local_size; j++) { //columns in multiply
            for (k = 0; k < local_size; k++) { //columns in first and rows in second
                sum = sum + first[i][k]*second[k][j];
            }
            multiply[i][j] = sum;
            sum = 0;
        }
    }
    return 0;
}

int mm4(double first[][SIZE], double second[][SIZE], double multiply[][SIZE])
{
    register unsigned int i,j,k; //<- OPT 1
    register unsigned int local_size=SIZE; //<- OPT 2
    double sum = 0;
    for (i = SIZE; i-- ; ) { //rows in multiply <- OPT 3
        for (j = SIZE; j-- ;) { //columns in multiply
            for (k = SIZE; k-- ; ) { //columns in first and rows in second
                sum = sum + first[i][k]*second[k][j];
            }
            multiply[i][j] = sum;
            sum = 0;
        }
    }
    return 0;
}

int mm5(double first[][SIZE], double second[][SIZE], double multiply[][SIZE])
{
    register unsigned int i,j,k; //<- OPT 1
    //  register unsigned int local_size=SIZE; //<- OPT 2
    register double sum = 0;
    for (i = SIZE; i-- ; ) { //rows in multiply <- OPT 3
        for (j = SIZE; j-- ;) { //columns in multiply
            for (k = 0; k < SIZE; ) {
                if(k<SIZE-8) { //<- OPT 4
                    sum = sum + first[i][k]*second[k][j]
                          + first[i][k+1]*second[k+1][j]
                          + first[i][k+2]*second[k+2][j]
                          + first[i][k+3]*second[k+3][j]
                          + first[i][k+4]*second[k+4][j]
                          + first[i][k+5]*second[k+5][j]
                          + first[i][k+6]*second[k+6][j]
                          + first[i][k+7]*second[k+7][j];
                    k=k+8;
                }
                else {
                    sum = sum + first[i][k]*second[k][j];
                    k++;
                }
            }
            multiply[i][j] = sum;
            sum = 0;
        }
    }
    return 0;
}

int mm51(double first[][SIZE], double second[][SIZE], double multiply[][SIZE])
{
    register unsigned int i,j,k; //<- OPT 1
    register unsigned int local_size=SIZE; //<- OPT 2
    register double sum = 0;
    for (i = SIZE; i-- ; ) { //rows in multiply <- OPT 3
        for (j = SIZE; j-- ;) { //columns in multiply
            for (k = 0; k < SIZE; ) {
                if(k<SIZE-8) { //<- OPT 4
                    sum = sum + first[i][k]*second[k][j];
                    sum = sum + first[i][k+1]*second[k+1][j];
                    sum = sum + first[i][k+2]*second[k+2][j];
                    sum = sum + first[i][k+3]*second[k+3][j];
                    sum = sum + first[i][k+4]*second[k+4][j];
                    sum = sum + first[i][k+5]*second[k+5][j];
                    sum = sum + first[i][k+6]*second[k+6][j];
                    sum = sum + first[i][k+7]*second[k+7][j];
                    k=k+8;
                }
                else {
                    sum = sum + first[i][k]*second[k][j];
                    k++;
                }
            }
            multiply[i][j] = sum;
            sum = 0;
        }
    }
    return 0;
}

int mm52(double first[][SIZE], double second[][SIZE], double multiply[][SIZE])
{
    register unsigned int i,j,k; //<- OPT 1
    register unsigned int local_size=SIZE; //<- OPT 2
    register double sum = 0;
    for (i = SIZE; i-- ; ) { //rows in multiply <- OPT 3
        for (j = SIZE; j-- ;) { //columns in multiply
            for (k = 0; k < SIZE; ) {
                if(k<SIZE-8) { //<- OPT 4
                    sum = sum + first[i][k]*second[k][j];
                    sum = sum + first[i][k+1]*second[k+1][j];
                    sum = sum + first[i][k+2]*second[k+2][j];
                    sum = sum + first[i][k+3]*second[k+3][j];
                    sum = sum + first[i][k+4]*second[k+4][j];
                    sum = sum + first[i][k+5]*second[k+5][j];
                    sum = sum + first[i][k+6]*second[k+6][j];
                    sum = sum + first[i][k+7]*second[k+7][j];
                    k=k+8;
                }
                else {
                    sum = sum + first[i][k]*second[k][j];
                    k++;
                }
            }
            multiply[i][j] = sum;
            sum = 0;
        }
    }
    return 0;
}

int mm6(double first[][SIZE], double second[][SIZE], double multiply[][SIZE])
{
    register unsigned int i,j,k; //<- OPT 1
    //  register unsigned int local_size=SIZE; //<- OPT 2
    register double sum = 0;
    for (i = SIZE; i-- ; ) { //rows in multiply <- OPT 3
        for (j = SIZE; j-- ;) { //columns in multiply
            for (k=0; k<SIZE; ){
                if(k<SIZE-8) { //<- OPT 4
                    sum = sum + first[i][k]*second[j][k] //<- OPT 5 (k<->j)
                          + first[i][k+1]*second[j][k+1]
                          + first[i][k+2]*second[j][k+2]
                          + first[i][k+3]*second[j][k+3]
                          + first[i][k+4]*second[j][k+4]
                          + first[i][k+5]*second[j][k+5]
                          + first[i][k+6]*second[j][k+6]
                          + first[i][k+7]*second[j][k+7];
                    k=k+8;
                }
                else {
                    sum = sum + first[i][k]*second[j][k];
                    k++;
                }
            }
            multiply[i][j] = sum;
            sum=0.0;
        }
    }
    return 0;
}


int mm7(double first[][SIZE], double second[][SIZE], double multiply[][SIZE])
{
    register unsigned int i,j,k; //<- OPT 1
    register unsigned int local_size=SIZE; //<- OPT 2
    double sum = 0;
    for (i = 0; i<SIZE ; i++ ) { //rows in multiply <- OPT 3
        for (j=0; j<SIZE; ) {
            for (k=0; k<SIZE; ) {

                sum = sum + first[i][k]*second[j][k] //<- OPT 5 (k<->j)
                      + first[i][k+1]*second[j][k+1]
                      + first[i][k+2]*second[j][k+2]
                      + first[i][k+3]*second[j][k+3]
                      + first[i][k+4]*second[j][k+4]
                      + first[i][k+5]*second[j][k+5]
                      + first[i][k+6]*second[j][k+6]
                      + first[i][k+7]*second[j][k+7];
                multiply[i][j]+=sum; sum=0;

                sum = sum + first[i][k]*second[j+1][k] //<- OPT 5 (k<->j+1)
                      + first[i][k+1]*second[j+1][k+1]
                      + first[i][k+2]*second[j+1][k+2]
                      + first[i][k+3]*second[j+1][k+3]
                      + first[i][k+4]*second[j+1][k+4]
                      + first[i][k+5]*second[j+1][k+5]
                      + first[i][k+6]*second[j+1][k+6]
                      + first[i][k+7]*second[j+1][k+7];
                multiply[i][j+1]+=sum; sum=0;

                sum = sum + first[i][k]*second[j+2][k] //<- OPT 5 (k<->j+2)
                      + first[i][k+1]*second[j+2][k+1]
                      + first[i][k+2]*second[j+2][k+2]
                      + first[i][k+3]*second[j+2][k+3]
                      + first[i][k+4]*second[j+2][k+4]
                      + first[i][k+5]*second[j+2][k+5]
                      + first[i][k+6]*second[j+2][k+6]
                      + first[i][k+7]*second[j+2][k+7];
                multiply[i][j+2]+=sum; sum=0;

                sum = sum + first[i][k]*second[j+3][k] //<- OPT 5 (k<->j+3)
                      + first[i][k+1]*second[j+3][k+1]
                      + first[i][k+2]*second[j+3][k+2]
                      + first[i][k+3]*second[j+3][k+3]
                      + first[i][k+4]*second[j+3][k+4]
                      + first[i][k+5]*second[j+3][k+5]
                      + first[i][k+6]*second[j+3][k+6]
                      + first[i][k+7]*second[j+3][k+7];
                multiply[i][j+3]+=sum; sum=0;

                sum = sum + first[i][k]*second[j+4][k] //<- OPT 5 (k<->j+4)
                      + first[i][k+1]*second[j+4][k+1]
                      + first[i][k+2]*second[j+4][k+2]
                      + first[i][k+3]*second[j+4][k+3]
                      + first[i][k+4]*second[j+4][k+4]
                      + first[i][k+5]*second[j+4][k+5]
                      + first[i][k+6]*second[j+4][k+6]
                      + first[i][k+7]*second[j+4][k+7];
                multiply[i][j+4]+=sum; sum=0;

                sum = sum + first[i][k]*second[j+5][k] //<- OPT 5 (k<->j+5)
                      + first[i][k+1]*second[j+5][k+1]
                      + first[i][k+2]*second[j+5][k+2]
                      + first[i][k+3]*second[j+5][k+3]
                      + first[i][k+4]*second[j+5][k+4]
                      + first[i][k+5]*second[j+5][k+5]
                      + first[i][k+6]*second[j+5][k+6]
                      + first[i][k+7]*second[j+5][k+7];
                multiply[i][j+5]+=sum; sum=0;

                sum = sum + first[i][k]*second[j+6][k] //<- OPT 5 (k<->j+6)
                      + first[i][k+1]*second[j+6][k+1]
                      + first[i][k+2]*second[j+6][k+2]
                      + first[i][k+3]*second[j+6][k+3]
                      + first[i][k+4]*second[j+6][k+4]
                      + first[i][k+5]*second[j+6][k+5]
                      + first[i][k+6]*second[j+6][k+6]
                      + first[i][k+7]*second[j+6][k+7];
                multiply[i][j+6]+=sum; sum=0;

                sum = sum + first[i][k]*second[j+7][k] //<- OPT 5 (k<->j+7)
                      + first[i][k+1]*second[j+7][k+1]
                      + first[i][k+2]*second[j+7][k+2]
                      + first[i][k+3]*second[j+7][k+3]
                      + first[i][k+4]*second[j+7][k+4]
                      + first[i][k+5]*second[j+7][k+5]
                      + first[i][k+6]*second[j+7][k+6]
                      + first[i][k+7]*second[j+7][k+7];
                multiply[i][j+7]+=sum; sum=0;

                k=k+8;
            }
            j=j+8;
        }
    }
    return 0;
}

int mm8(double first[][SIZE], double second[][SIZE], double multiply[][SIZE])
{
    register unsigned int i,j,k; //<- OPT 1
    //  register unsigned int local_size=SIZE; //<- OPT 2
    double sum = 0;
    for (i = 0; i<SIZE ; i++ ) { //rows in multiply <- OPT 3
        for (j=0; j<SIZE; ) {
            for (k=0; k<SIZE; ) {

                register double f1=first[i][k];
                register double f2=first[i][k+1];
                register double f3=first[i][k+2];
                register double f4=first[i][k+3];
                register double f5=first[i][k+4];
                register double f6=first[i][k+5];
                register double f7=first[i][k+6];
                register double f8=first[i][k+7];
                sum = sum + f1*second[j][k] //<- OPT 5 (k<->j)
                      + f2*second[j][k+1]
                      + f3*second[j][k+2]
                      + f4*second[j][k+3]
                      + f5*second[j][k+4]
                      + f6*second[j][k+5]
                      + f7*second[j][k+6]
                      + f8*second[j][k+7];
                multiply[i][j]+=sum; sum=0;

                sum = sum + f1*second[j+1][k] //<- OPT 5 (k<->j+1)
                      + f2*second[j+1][k+1]
                      + f3*second[j+1][k+2]
                      + f4*second[j+1][k+3]
                      + f5*second[j+1][k+4]
                      + f6*second[j+1][k+5]
                      + f7*second[j+1][k+6]
                      + f8*second[j+1][k+7];
                multiply[i][j+1]+=sum; sum=0;

                sum = sum + f1*second[j+2][k] //<- OPT 5 (k<->j+2)
                      + f2*second[j+2][k+1]
                      + f3*second[j+2][k+2]
                      + f4*second[j+2][k+3]
                      + f5*second[j+2][k+4]
                      + f6*second[j+2][k+5]
                      + f7*second[j+2][k+6]
                      + f8*second[j+2][k+7];
                multiply[i][j+2]+=sum; sum=0;

                sum = sum + f1*second[j+3][k] //<- OPT 5 (k<->j+3)
                      + f2*second[j+3][k+1]
                      + f3*second[j+3][k+2]
                      + f4*second[j+3][k+3]
                      + f5*second[j+3][k+4]
                      + f6*second[j+3][k+5]
                      + f7*second[j+3][k+6]
                      + f8*second[j+3][k+7];
                multiply[i][j+3]+=sum; sum=0;

                sum = sum + f1*second[j+4][k] //<- OPT 5 (k<->j+4)
                      + f2*second[j+4][k+1]
                      + f3*second[j+4][k+2]
                      + f4*second[j+4][k+3]
                      + f5*second[j+4][k+4]
                      + f6*second[j+4][k+5]
                      + f7*second[j+4][k+6]
                      + f8*second[j+4][k+7];
                multiply[i][j+4]+=sum; sum=0;

                sum = sum + f1*second[j+5][k] //<- OPT 5 (k<->j+5)
                      + f2*second[j+5][k+1]
                      + f3*second[j+5][k+2]
                      + f4*second[j+5][k+3]
                      + f5*second[j+5][k+4]
                      + f6*second[j+5][k+5]
                      + f7*second[j+5][k+6]
                      + f8*second[j+5][k+7];
                multiply[i][j+5]+=sum; sum=0;

                sum = sum + f1*second[j+6][k] //<- OPT 5 (k<->j+6)
                      + f2*second[j+6][k+1]
                      + f3*second[j+6][k+2]
                      + f4*second[j+6][k+3]
                      + f5*second[j+6][k+4]
                      + f6*second[j+6][k+5]
                      + f7*second[j+6][k+6]
                      + f8*second[j+6][k+7];
                multiply[i][j+6]+=sum; sum=0;

                sum = sum + f1*second[j+7][k] //<- OPT 5 (k<->j+6)
                      + f2*second[j+7][k+1]
                      + f3*second[j+7][k+2]
                      + f4*second[j+7][k+3]
                      + f5*second[j+7][k+4]
                      + f6*second[j+7][k+5]
                      + f7*second[j+7][k+6]
                      + f8*second[j+7][k+7];
                multiply[i][j+7]+=sum; sum=0;

                k=k+8;
            }
            j=j+8;
        }
    }
    return 0;
}

int mm9(double first[][SIZE], double second[][SIZE], double multiply[][SIZE])
{
    register unsigned int i,j,k; //<- OPT 1
    //  register unsigned int local_size=SIZE; //<- OPT 2
    double sum = 0;
    for (i = 0; i<SIZE ; i++ ) { //rows in multiply <- OPT 3
        for (j=0; j<SIZE; ) {
            for (k=0; k<SIZE; ) {
                register double f1=first[i][k];
                register double f2=first[i][k+1];
                register double f3=first[i][k+2];
                register double f4=first[i][k+3];
                register double f5=first[i][k+4];
                register double f6=first[i][k+5];
                register double f7=first[i][k+6];
                register double f8=first[i][k+7];
                register double f9=first[i][k+8];
                register double f10=first[i][k+9];
                register double f11=first[i][k+10];
                register double f12=first[i][k+11];
                register double f13=first[i][k+12];
                register double f14=first[i][k+13];
                register double f15=first[i][k+14];
                register double f16=first[i][k+15];
                sum = sum + f1*second[j][k] //<- OPT 5 (k<->j)
                      + f2*second[j][k+1]
                      + f3*second[j][k+2]
                      + f4*second[j][k+3]
                      + f5*second[j][k+4]
                      + f6*second[j][k+5]
                      + f7*second[j][k+6]
                      + f8*second[j][k+7]
                      + f9*second[j][k+8]
                      + f10*second[j][k+9]
                      + f11*second[j][k+10]
                      + f12*second[j][k+11]
                      + f13*second[j][k+12]
                      + f14*second[j][k+13]
                      + f15*second[j][k+14]
                      + f16*second[j][k+15];
                multiply[i][j]+=sum; sum=0;

                sum = sum + f1*second[j+1][k] //<- OPT 5 (k<->j+1)
                      + f2*second[j+1][k+1]
                      + f3*second[j+1][k+2]
                      + f4*second[j+1][k+3]
                      + f5*second[j+1][k+4]
                      + f6*second[j+1][k+5]
                      + f7*second[j+1][k+6]
                      + f8*second[j+1][k+7]
                      + f9*second[j+1][k+8]
                      + f10*second[j+1][k+9]
                      + f11*second[j+1][k+10]
                      + f12*second[j+1][k+11]
                      + f13*second[j+1][k+12]
                      + f14*second[j+1][k+13]
                      + f15*second[j+1][k+14]
                      + f16*second[j+1][k+15];
                multiply[i][j+1]+=sum; sum=0;

                sum = sum + f1*second[j+2][k] //<- OPT 5 (k<->j+2)
                      + f2*second[j+2][k+1]
                      + f3*second[j+2][k+2]
                      + f4*second[j+2][k+3]
                      + f5*second[j+2][k+4]
                      + f6*second[j+2][k+5]
                      + f7*second[j+2][k+6]
                      + f8*second[j+2][k+7]
                      + f9*second[j+2][k+8]
                      + f10*second[j+2][k+9]
                      + f11*second[j+2][k+10]
                      + f12*second[j+2][k+11]
                      + f13*second[j+2][k+12]
                      + f14*second[j+2][k+13]
                      + f15*second[j+2][k+14]
                      + f16*second[j+2][k+15];
                multiply[i][j+2]+=sum; sum=0;

                sum = sum + f1*second[j+3][k] //<- OPT 5 (k<->j+3)
                      + f2*second[j+3][k+1]
                      + f3*second[j+3][k+2]
                      + f4*second[j+3][k+3]
                      + f5*second[j+3][k+4]
                      + f6*second[j+3][k+5]
                      + f7*second[j+3][k+6]
                      + f8*second[j+3][k+7]
                      + f9*second[j+3][k+8]
                      + f10*second[j+3][k+9]
                      + f11*second[j+3][k+10]
                      + f12*second[j+3][k+11]
                      + f13*second[j+3][k+12]
                      + f14*second[j+3][k+13]
                      + f15*second[j+3][k+14]
                      + f16*second[j+3][k+15];
                multiply[i][j+3]+=sum; sum=0;

                sum = sum + f1*second[j+4][k] //<- OPT 5 (k<->j+4)
                      + f2*second[j+4][k+1]
                      + f3*second[j+4][k+2]
                      + f4*second[j+4][k+3]
                      + f5*second[j+4][k+4]
                      + f6*second[j+4][k+5]
                      + f7*second[j+4][k+6]
                      + f8*second[j+4][k+7]
                      + f9*second[j+4][k+8]
                      + f10*second[j+4][k+9]
                      + f11*second[j+4][k+10]
                      + f12*second[j+4][k+11]
                      + f13*second[j+4][k+12]
                      + f14*second[j+4][k+13]
                      + f15*second[j+4][k+14]
                      + f16*second[j+4][k+15];
                multiply[i][j+4]+=sum; sum=0;

                sum = sum + f1*second[j+5][k] //<- OPT 5 (k<->j+5)
                      + f2*second[j+5][k+1]
                      + f3*second[j+5][k+2]
                      + f4*second[j+5][k+3]
                      + f5*second[j+5][k+4]
                      + f6*second[j+5][k+5]
                      + f7*second[j+5][k+6]
                      + f8*second[j+5][k+7]
                      + f9*second[j+5][k+8]
                      + f10*second[j+5][k+9]
                      + f11*second[j+5][k+10]
                      + f12*second[j+5][k+11]
                      + f13*second[j+5][k+12]
                      + f14*second[j+5][k+13]
                      + f15*second[j+5][k+14]
                      + f16*second[j+5][k+15];
                multiply[i][j+5]+=sum; sum=0;

                sum = sum + f1*second[j+6][k] //<- OPT 5 (k<->j+6)
                      + f2*second[j+6][k+1]
                      + f3*second[j+6][k+2]
                      + f4*second[j+6][k+3]
                      + f5*second[j+6][k+4]
                      + f6*second[j+6][k+5]
                      + f7*second[j+6][k+6]
                      + f8*second[j+6][k+7]
                      + f9*second[j+6][k+8]
                      + f10*second[j+6][k+9]
                      + f11*second[j+6][k+10]
                      + f12*second[j+6][k+11]
                      + f13*second[j+6][k+12]
                      + f14*second[j+6][k+13]
                      + f15*second[j+6][k+14]
                      + f16*second[j+6][k+15];
                multiply[i][j+6]+=sum; sum=0;

                sum = sum + f1*second[j+7][k] //<- OPT 5 (k<->j+6)
                      + f2*second[j+7][k+1]
                      + f3*second[j+7][k+2]
                      + f4*second[j+7][k+3]
                      + f5*second[j+7][k+4]
                      + f6*second[j+7][k+5]
                      + f7*second[j+7][k+6]
                      + f8*second[j+7][k+7]
                      + f9*second[j+7][k+8]
                      + f10*second[j+7][k+9]
                      + f11*second[j+7][k+10]
                      + f12*second[j+7][k+11]
                      + f13*second[j+7][k+12]
                      + f14*second[j+7][k+13]
                      + f15*second[j+7][k+14]
                      + f16*second[j+7][k+15];
                multiply[i][j+7]+=sum; sum=0;

                sum = sum + f1*second[j+8][k] //<- OPT 5 (k<->j+8)
                      + f2*second[j+8][k+1]
                      + f3*second[j+8][k+2]
                      + f4*second[j+8][k+3]
                      + f5*second[j+8][k+4]
                      + f6*second[j+8][k+5]
                      + f7*second[j+8][k+6]
                      + f8*second[j+8][k+7]
                      + f9*second[j+8][k+8]
                      + f10*second[j+8][k+9]
                      + f11*second[j+8][k+10]
                      + f12*second[j+8][k+11]
                      + f13*second[j+8][k+12]
                      + f14*second[j+8][k+13]
                      + f15*second[j+8][k+14]
                      + f16*second[j+8][k+15];
                multiply[i][j+8]+=sum; sum=0;

                sum = sum + f1*second[j+9][k] //<- OPT 5 (k<->j+9)
                      + f2*second[j+9][k+1]
                      + f3*second[j+9][k+2]
                      + f4*second[j+9][k+3]
                      + f5*second[j+9][k+4]
                      + f6*second[j+9][k+5]
                      + f7*second[j+9][k+6]
                      + f8*second[j+9][k+7]
                      + f9*second[j+9][k+8]
                      + f10*second[j+9][k+9]
                      + f11*second[j+9][k+10]
                      + f12*second[j+9][k+11]
                      + f13*second[j+9][k+12]
                      + f14*second[j+9][k+13]
                      + f15*second[j+9][k+14]
                      + f16*second[j+9][k+15];
                multiply[i][j+9]+=sum; sum=0;

                sum = sum + f1*second[j+10][k] //<- OPT 5 (k<->j+10)
                      + f2*second[j+10][k+1]
                      + f3*second[j+10][k+2]
                      + f4*second[j+10][k+3]
                      + f5*second[j+10][k+4]
                      + f6*second[j+10][k+5]
                      + f7*second[j+10][k+6]
                      + f8*second[j+10][k+7]
                      + f9*second[j+10][k+8]
                      + f10*second[j+10][k+9]
                      + f11*second[j+10][k+10]
                      + f12*second[j+10][k+11]
                      + f13*second[j+10][k+12]
                      + f14*second[j+10][k+13]
                      + f15*second[j+10][k+14]
                      + f16*second[j+10][k+15];
                multiply[i][j+10]+=sum; sum=0;

                sum = sum + f1*second[j+11][k] //<- OPT 5 (k<->j+11)
                      + f2*second[j+11][k+1]
                      + f3*second[j+11][k+2]
                      + f4*second[j+11][k+3]
                      + f5*second[j+11][k+4]
                      + f6*second[j+11][k+5]
                      + f7*second[j+11][k+6]
                      + f8*second[j+11][k+7]
                      + f9*second[j+11][k+8]
                      + f10*second[j+11][k+9]
                      + f11*second[j+11][k+10]
                      + f12*second[j+11][k+11]
                      + f13*second[j+11][k+12]
                      + f14*second[j+11][k+13]
                      + f15*second[j+11][k+14]
                      + f16*second[j+11][k+15];
                multiply[i][j+11]+=sum; sum=0;

                sum = sum + f1*second[j+12][k] //<- OPT 5 (k<->j+12)
                      + f2*second[j+12][k+1]
                      + f3*second[j+12][k+2]
                      + f4*second[j+12][k+3]
                      + f5*second[j+12][k+4]
                      + f6*second[j+12][k+5]
                      + f7*second[j+12][k+6]
                      + f8*second[j+12][k+7]
                      + f9*second[j+12][k+8]
                      + f10*second[j+12][k+9]
                      + f11*second[j+12][k+10]
                      + f12*second[j+12][k+11]
                      + f13*second[j+12][k+12]
                      + f14*second[j+12][k+13]
                      + f15*second[j+12][k+14]
                      + f16*second[j+12][k+15];
                multiply[i][j+12]+=sum; sum=0;

                sum = sum + f1*second[j+13][k] //<- OPT 5 (k<->j+13)
                      + f2*second[j+13][k+1]
                      + f3*second[j+13][k+2]
                      + f4*second[j+13][k+3]
                      + f5*second[j+13][k+4]
                      + f6*second[j+13][k+5]
                      + f7*second[j+13][k+6]
                      + f8*second[j+13][k+7]
                      + f9*second[j+13][k+8]
                      + f10*second[j+13][k+9]
                      + f11*second[j+13][k+10]
                      + f12*second[j+13][k+11]
                      + f13*second[j+13][k+12]
                      + f14*second[j+13][k+13]
                      + f15*second[j+13][k+14]
                      + f16*second[j+13][k+15];
                multiply[i][j+13]+=sum; sum=0;

                sum = sum + f1*second[j+14][k] //<- OPT 5 (k<->j+14)
                      + f2*second[j+14][k+1]
                      + f3*second[j+14][k+2]
                      + f4*second[j+14][k+3]
                      + f5*second[j+14][k+4]
                      + f6*second[j+14][k+5]
                      + f7*second[j+14][k+6]
                      + f8*second[j+14][k+7]
                      + f9*second[j+14][k+8]
                      + f10*second[j+14][k+9]
                      + f11*second[j+14][k+10]
                      + f12*second[j+14][k+11]
                      + f13*second[j+14][k+12]
                      + f14*second[j+14][k+13]
                      + f15*second[j+14][k+14]
                      + f16*second[j+14][k+15];
                multiply[i][j+14]+=sum; sum=0;

                sum = sum + f1*second[j+15][k] //<- OPT 5 (k<->j+15)
                      + f2*second[j+15][k+1]
                      + f3*second[j+15][k+2]
                      + f4*second[j+15][k+3]
                      + f5*second[j+15][k+4]
                      + f6*second[j+15][k+5]
                      + f7*second[j+15][k+6]
                      + f8*second[j+15][k+7]
                      + f9*second[j+15][k+8]
                      + f10*second[j+15][k+9]
                      + f11*second[j+15][k+10]
                      + f12*second[j+15][k+11]
                      + f13*second[j+15][k+12]
                      + f14*second[j+15][k+13]
                      + f15*second[j+15][k+14]
                      + f16*second[j+15][k+15];
                multiply[i][j+15]+=sum; sum=0;

                k=k+16;
            }
            j=j+16;
        }
    }
    return 0;
}