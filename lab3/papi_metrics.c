#ifndef __USE_GNU
#define __USE_GNU
#endif
#define _GNU_SOURCE
#include <sched.h>


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <papi.h>
#include "mm.h"

int main() {

    int (*algorithm)(double first[][SIZE], double second[][SIZE], double multiply[][SIZE]) = NULL;
    #ifndef ALGORITHM
        #define ALGORITHM 1
    #endif

    switch (ALGORITHM){
        case 1:
            algorithm = &mm1;
            break;
        case 2:
            algorithm = &mm2;
            break;
        case 3:
            algorithm = &mm3;
            break;
        case 4:
            algorithm = &mm4;
            break;
        case 5:
            algorithm = &mm5;
            break;
        case 51:
            algorithm = &mm51;
            break;
        case 52:
            algorithm = &mm52;
            break;
        case 6:
            algorithm = &mm6;
            break;
        case 7:
            algorithm = &mm7;
            break;
        case 8:
            algorithm = &mm8;
            break;
        case 9:
            algorithm = &mm9;
            break;
        default:
            algorithm = &mm1;
    }

    int i, j;
    double first[SIZE][SIZE];
    double second[SIZE][SIZE];
    double multiply[SIZE][SIZE];

    for (i = 0; i < SIZE; i++) { //rows in first
        for (j = 0; j < SIZE; j++) { //columns in first
            first[i][j]=i+j;
            second[i][j]=i-j;
            multiply[i][j]=0.0;
        }
    }

    /* force program to run on a single CPU */
    cpu_set_t my_set;        /* Define your cpu_set bit mask. */
    CPU_ZERO(&my_set);       /* Initialize it all to 0, i.e. no CPUs selected. */
    CPU_SET(0, &my_set);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &my_set) != 0)
        perror("sched_setaffinity error");

    /* init lib */
    int events[4] = {
            PAPI_STL_ICY, //Cycles with no instruction issue
            PAPI_L2_DCM, //L2 data cache misses
            PAPI_L2_ICH, //L2 instruction cache hits
            PAPI_TOT_INS //Instructions completed
    };
    long long values[4] = {0,0,0,0};
    int eventSet = PAPI_NULL;
    int papi_err;
    bool papi_supported = true;

    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
        fprintf(stderr, "PAPI is unsupported.\n");
        papi_supported = false;
    }

    if (PAPI_num_counters() < 4) {
        fprintf(stderr, "PAPI is unsupported.\n");
        papi_supported = false;
    }

    if ((papi_err = PAPI_create_eventset(&eventSet)) != PAPI_OK) {
        fprintf(stderr, "Could not create event set: %s\n", PAPI_strerror(papi_err));
    }

    for (i=0; i<4; ++i) {
        if ((papi_err = PAPI_add_event(eventSet, events[i])) != PAPI_OK ) {
            fprintf(stderr, "Could not add event %d: %s\n", i, PAPI_strerror(papi_err));
        }
    }

    /* start counters */
    if (papi_supported) {
        if ((papi_err = PAPI_start(eventSet)) != PAPI_OK) {
            fprintf(stderr, "Could not start counters: %s\n", PAPI_strerror(papi_err));
        }
    }

    algorithm(first,second,multiply);


    /* stop counters */
    if (papi_supported) {
        if ((papi_err = PAPI_stop(eventSet, values)) != PAPI_OK) {
            fprintf(stderr, "Could not get values: %s\n", PAPI_strerror(papi_err));
        }

        int save_to_file = 0;
        if (save_to_file > 0){
            FILE *fp;
            char filename[50];
            sprintf(filename, "results/multiple_events/algo%d.txt", ALGORITHM);
            fp = fopen(filename, "w+");
            if (fp == NULL) perror("Error while saving results to file");
            fprintf(fp, "1: %lld\n", values[0]);
            fprintf(fp, "2: %lld\n", values[1]);
            fprintf(fp, "3: %lld\n", values[2]);
            fprintf(fp, "4: %lld\n", values[3]);
            fclose(fp);
        }

        printf("Performance counters for factorization stage: \n");
        printf("\tAlgorithm: %d\n", ALGORITHM);
        printf("\tSTL ICY (Cycles with no instruction issue): %lld\n", values[0]);
        printf("\tL2 DCM              (L2 Data Cache Misses): %lld\n", values[1]);
        printf("\tL2 ICH        (L2 Instructions Cache Hits): %lld\n", values[2]);
        printf("\tTOT INS           (Instructions completed): %lld\n", values[3]);
    }
}