#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Arrays.h"

double* subsRev(double **mat, double *b, int m){
  double soma;
  double* raiz = (double*)malloc(m*sizeof(double));

  for (int i=m-1; i>=0; i--){
    soma = 0;
    for (int j=m-1; j>i; j--) 
      soma += raiz[j]*mat[i][j]; //mudanca
    raiz[i] = (b[i] - soma)/mat[i][i];
  }
  return (raiz);
}
double* subsProg(double **mat, double *b, int m){
  double soma;
  double* raiz = (double*)malloc(m*sizeof(double));

  for(int i=0; i<m; i++){
    soma = 0;
    for(int j=0; j<i; j++)
      soma += raiz[j]*mat[i][j];  //mudanca
    raiz[i] = (b[i] - soma)/mat[i][i];
  }
  return (raiz);
}
double **inversa(double **mat, int m, int n){
  double pivot, lambda, temp;
  int lp;

  //alocacao de vetores
  double* x = malloc(m * sizeof(double));
  double* y = malloc(m * sizeof(double));

  //alocacao de matrizes
  double** U = aloc(m, n);
  double** Z = aloc(m, (n-m));

  //alocacao de uma matriz L zerada e copia das linhas de mat para U, aproveitando o laco 'for'
  double** L = (double**)calloc(m, sizeof(double*));
  for (int i=0; i<m; i++){
      L[i] = (double*)calloc(n, sizeof(double));
      memcpy(U[i], mat[i], n*sizeof(double*));
  }

  for(int k=0; k<m; k++) {
    pivot = fabs(U[k][k]);
    lp = k;
    for(int l = k + 1; l < m; l++) {
      temp = fabs(U[l][k]);
      if(temp > pivot) {
        lp = l;
        pivot = temp;
      }
    }
    if(lp != k){
      troca(&U[lp], &U[k]);
      troca(&L[lp], &L[k]);
    }

    if(pivot==0){
      puts("Sistema sem Solução!!");
      Z = NULL;
      return Z;
    }

    // triangularizacao da Matriz
    for(int j = k + 1; j < m; j++){
      lambda = U[j][k] / U[k][k];  ///mudanca
      L[j][k] = lambda; 
      for(int i = k; i < m; i++){
        U[j][i] += -U[k][i] * lambda;
      }
    }
  }

  for(int k=0; k<m; k++) 
    L[k][k]=1;

  for (int j=m; j<n; j++){
    for(int i = 0; i < m; i++) 
      x[i] = U[i][j];

    y = subsProg(L, x, m);  //substituicoes
    x = subsRev(U, y, m);
    for(int k=0; k<m; k++) 
      Z[k][j-m] = x[k];
  }

  liberaMatriz(U, m);
  liberaMatriz(L, m);
  free(x);
  free(y);
  return Z;
}
double normaFrobenius(double** mat, int m){
  double soma=0;

  for(int i=0; i<m; i++){
    for(int j=0; j<m; j++){
      soma += pow(mat[i][j], 2);
    }
  }
  return sqrt(soma);  //retorna a raiz da soma dos quadrados da matriz
}
double normaVetor(double  *vet, int m, int p){
  double norma=0, maior=0;

  if (p) {
    for (int i=0; i<m; i++)
      norma+= pow(fabs(vet[i]),p);
    norma = pow(norma, 1./p);
  }
  else {
    for (int i=0; i<m; i++) {
      maior = fabs(vet[i]);
      norma = (maior>norma) ?  maior:norma;
    }  
  }
  return norma;
}
double normaMatriz(double **mat, int m, int n, int p){
  double *vet = malloc(m*sizeof(double)); //armazenar os resultados da norma de cada coluna
  for (int i=0; i<m; i++)
    vet[i] = normaVetor(mat[i], n, p); //Calcula a norma de cada vetor da matriz

  return normaVetor(vet, m, p); // Calcula a norma do vetor de resultados
}
double residuo(double **mat, int m, int n, int p){
  double resp = 0;
  
  switch(p){
    case 0:
    case 1:
      return normaMatriz(mat, m, n, p);
    break;

    case 2:
      return normaFrobenius(mat, m);
    break;

    default:
      printf("Opcao invalida para p. (%d)", p);
    break;
  }
  return resp;
}