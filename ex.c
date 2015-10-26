#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <papi.h>


int main() {

    /* init lib */
    int events[5] = {PAPI_FP_OPS, PAPI_LD_INS, PAPI_SR_INS, PAPI_L1_DCM, PAPI_L2_TCM};
    long long values[5] = {0,};
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

    for (i=0; i<5; ++i) {
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


    /* stop conuters */


    if (papi_supported) {
        if ((papi_err = PAPI_stop(eventSet, values)) != PAPI_OK) {
            fprintf(stderr, "Could not get values: %s\n", PAPI_strerror(papi_err));
        }
        // PAPI_FP_OPS
        // PAPI_LD_INS
        // PAPI_SR_INS
        // PAPI_L1_DCM
        // PAPI_L2_TCM
        printf("Performance counters for factorization stage: \n");
        printf("\tFP OPS: %ld\n", values[0]);
        printf("\tLD INS: %ld\n", values[1]);
        printf("\tSR INS: %ld\n", values[2]);
        printf("\tL1 DCM: %ld\n", values[3]);
        printf("\tL2 TCM: %ld\n", values[4]);

    }
}