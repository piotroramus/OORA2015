//
// Created by piotr on 09.11.15.
//

#ifndef __USE_GNU
#define __USE_GNU
#endif
#define _GNU_SOURCE
#include <sched.h>


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <papi.h>

#include "papi_template.h"


int measure(int (*f)(double *A, int n), double *A, int n, int event) {

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
            "Cycles with no instruction issue: ",
            "L2 data cache misses:             ",
            "L2 data cache hits:               ",
            "Floating point operations:        "
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

    if ((papi_err = PAPI_add_event(eventSet, events[event])) != PAPI_OK ) {
        fprintf(stderr, "Could not add event %d: %s\n", event, PAPI_strerror(papi_err));
    }

    /* start counters */
    if (papi_supported) {
        if ((papi_err = PAPI_start(eventSet)) != PAPI_OK) {
            fprintf(stderr, "Could not start counters: %s\n", PAPI_strerror(papi_err));
        }
    }

    f(A, n);

    /* stop counters */
    if (papi_supported) {
        if ((papi_err = PAPI_stop(eventSet, values)) != PAPI_OK) {
            fprintf(stderr, "Could not get values: %s\n", PAPI_strerror(papi_err));
        }

        int save_to_file = 0;
        if (save_to_file > 0){
            FILE *fp;
            char filename[60];
            sprintf(filename, "results/event%d.txt", event);
            fp = fopen(filename, "w+");
            if (fp == NULL) perror("Error while saving results to file");
            fprintf(fp, "%lld", values[0]);
            fclose(fp);
        }

        printf("%s\t %lld\n", event_names[event], values[0]);
    }
}