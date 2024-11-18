#ifndef ARRAYS_H
#define ARRAYS_H

//le um arquivo e grava em uma matriz retornada em um ponteiro
double** leMatriz(char* nome, int* m, int* n);

//printa uma matriz[m][n]
void printMatriz(char *nome, double **mat, int m, int n);

//libera a memoria alocada
void liberaMatriz(double** mat, int m);

//le um arquivo e grava em um vetor retornado em um ponteiro
double* leVetor(char *nome, int *m);

//printa um vetor[m]
void printVetor(char *nome, double *vet, int m);

//retorna a copia de um vetor
double* copyVet(double *vet, int m);

#endif
