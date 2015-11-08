#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <papi.h>


int main() {

    /* init lib */
    int events[4] = {
            PAPI_STL_ICY, //Cycles with no instruction issue
            PAPI_L2_DCM, //L2 Data Cache misses
            PAPI_L2_DCH, //L2 Data Cache hits
            PAPI_FP_OPS //number of floating point operations
            };
    long long values[4] = {0,0,0,0};
    int eventSet = PAPI_NULL;
    int papi_err;
    int i;
    bool papi_supported = true;

    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
        fprintf(stderr, "PAPI is unsupported.\n");
        papi_supported = false;
    }

    if (PAPI_num_counters() < 5) {
        fprintf(stderr, "PAPI is unsupported.\n");
        papi_supported = false;
    }

    if ((papi_err = PAPI_create_eventset(&eventSet)) != PAPI_OK) {
        fprintf(stderr, "Could not create event set: %s\n", PAPI_strerror(papi_err));
    }

    for (i=0; i<4; ++i) {
        if ((papi_err = PAPI_add_event(eventSet, events[i])) != PAPI_OK ) {
            fprintf(stderr, "Could not add event: %s\n", PAPI_strerror(papi_err));
        }
    }


    /* start counters */
    if (papi_supported) {
        if ((papi_err = PAPI_start(eventSet)) != PAPI_OK) {
            fprintf(stderr, "Could not start counters: %s\n", PAPI_strerror(papi_err));
        }
    }



    /* stop counters */
    if (papi_supported) {
        if ((papi_err = PAPI_stop(eventSet, values)) != PAPI_OK) {
            fprintf(stderr, "Could not get values: %s\n", PAPI_strerror(papi_err));
        }
        printf("Performance counters for factorization stage: \n");
        printf("\tSTL ICY (Cycles with no instruction issue): %ld\n", values[0]);
        printf("\tL2 DCM              (L2 Data Cache Misses): %ld\n", values[1]);
        printf("\tL2 DCH                (L2 Data Cache Hits): %ld\n", values[2]);
        printf("\tFP OPS        (Floating points operations): %ld\n", values[3]);
    }
}