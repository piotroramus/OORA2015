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

    #ifndef EVENT
        #define EVENT 1
    #endif

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
            PAPI_L2_DCH, //L2 data cache hits
            PAPI_FP_OPS //Floating point operations
    };
    char* event_names[4] = {
            "Cycles with no instruction issue",
            "L2 data cache misses",
            "L2 data cache hits",
            "Floating point operations"
    };

    long long values[1] = {0};
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

    if ((papi_err = PAPI_add_event(eventSet, events[EVENT])) != PAPI_OK ) {
        fprintf(stderr, "Could not add event %d: %s\n", i, PAPI_strerror(papi_err));
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
            char filename[60];
            sprintf(filename, "results/single_events/event%d_algo%d.txt", EVENT, ALGORITHM);
            fp = fopen(filename, "w+");
            if (fp == NULL) perror("Error while saving results to file");
            fprintf(fp, "%lld", values[0]);
            fclose(fp);
        }

        printf("Performance counters for factorization stage: \n");
        printf("\tAlgorithm: %d\n", ALGORITHM);
        printf("\t%s: %lld\n", event_names[EVENT], values[0]);
    }
}