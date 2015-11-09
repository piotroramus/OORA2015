#!/usr/bin/env bash

for algorithm in 1 2 3 4 5 6 7 8 9 51 52
do
    for event in 0 1 2 3
    do
        gcc papi_metrics_single.c mm.c -o papi_metrics_single -lpapi -static -DALGORITHM=$algorithm -DEVENT=$event
       ./papi_metrics_single
    done
done