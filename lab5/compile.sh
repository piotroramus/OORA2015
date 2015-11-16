#!/usr/bin/env bash

gcc chol_dense.c clock.c papi_template.c -o chol_dense -lm -lpapi