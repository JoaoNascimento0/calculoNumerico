#ifndef ARRAYS_H
#define ARRAYS_H

//metodo de troca linhas.
void troca(double** a, double** b);

//retorna uma matriz identidade de tamanho m.
double** identidade(int m);

//imprime uma mensagem e uma matriz de dimensao m x n.
void printMatriz(char* msg, double** mat, int m, int n);

//libera a memoria alocada para a matriz.
void liberaMatriz(double** mat, int m);

//retorna uma matriz alocada com dimensoes m x n.
double** aloc(int m, int n);

//abre o arquivo e retorna as dimensoes m x n e os valores da matriz.
double** leMatriz(char* nome, int* m, int* n);

//multiplica as matrizes A(Am x An) pela B(Bm x Bn).
double** multiplicaMatriz(double **A, int Am, int An, double **B, int Bm, int Bn);

//soma as matrizes a.M(m x n) pela b.N(p x q) aonde 'a' e 'b' sao escalares.
double** SomaMatriz(double** M, int Am, int An, double a, double** N, int Bm, int Bn, double b);

#endif