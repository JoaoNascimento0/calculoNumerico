#ifndef ALGLINEAR_H
#define ALGLINEAR_H

//Substituicoes.
double* subsRev(double** mat, double *b, int m);
double* subsProg(double** mat, double *b, int m);

//metodo que abriga o algoritmo de Decomposicao LU com pivotamento e implementa as substituicoes.
double** inversa(double** mat, int m, int n);

//norma frobenius de uma matriz m x m.
double normaFrobenius(double** mat, int m);

//metodos de norma de ordem p.
double normaVetor(double* vet, int m, int p);
double normaMatriz(double** mat, int m, int n, int p);

//escolhe a norma pedida a partir do indice p.
double residuo(double** mat, int m, int n, int p);

#endif