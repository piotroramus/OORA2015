//
// Created by piotr on 09.11.15.
//

#ifndef REPO_PAPI_TEMPLATE_H
#define REPO_PAPI_TEMPLATE_H

typedef enum {STANDARD, OPTIMIZED} Algo;
int measure(int (*f)(double *A, unsigned int n), double *A, unsigned int n, Algo algorithm);


#endif //REPO_PAPI_TEMPLATE_H
