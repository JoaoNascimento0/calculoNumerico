#ifndef METODOS_H
#define METODOS_H

//metodo de Gauss-Siedel.
double* gaussSiedel(double **mat, int m, int n, double *x, double tol, int *it);

//metodo de gradiente ou maxima descida.
double* gradiente(double **M, int m, int n, double *x, int p, double tol, int *it);

//retorna um vetor de solucoes numericas.
double* GradienteConjugado(double **M, int m, int n, double *x, int p, double tol, int *it);

#endif
