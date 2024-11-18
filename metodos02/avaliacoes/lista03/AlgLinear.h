#ifndef ALGLINEAR_H
#define ALGLINEAR_H

//norma de ordem p de um vetor
double normaVetor(double* vet, int m, int p);

//multiplica uma matriz por um vetor
double* multiplicaVetorMatriz(double **M, int m, double *x, int n);

//retorna o produto interno de dois vetores
double ProdutoInterno(double *x, double *y, int m);

//retorna o produto de dois vetores por dois escalares
double* ProdVetVet(double lbd1, double *x1, double lbd2, double *x2, int m);

//retorna o produto entre um vetor e um escalar
double* VetorxEscalar(double *v, int n, double k);

//||x* - x(k)||
double difVetor(double* a, double* b, int m);

#endif
