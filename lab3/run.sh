#!/usr/bin/env bash

for algorithm in 1 2 3 4 5 6 7 8 9 51 52
do
    gcc papi_metrics.c mm.c -o papi_metrics -lpapi -static -DALGORITHM=$algorithm -O3
    ./papi_metrics
done