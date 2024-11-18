#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Arrays.h"

//manipulacao de matrizes
double** leMatriz(char* nome, int* m, int* n){
  FILE* arq = fopen(nome, "rt");

  //parametros de tamanho linha e coluna
  fscanf(arq, "%d %d\n", m, n);

  //alocacao da nova matriz
  double** mat = (double**)malloc((*m)*sizeof(double*));
  for (int i=0; i<(*m); i++){
    mat[i] = (double*)malloc((*n)*sizeof(double));
  }

  //atribuicao de valores obtidos na matriz do arquivo.dat
  for(int i=0; i<(*m); i++){
    for(int j=0; j<(*n); j++){
      fscanf(arq, "%lf", &mat[i][j]);
    }
  }
  fclose(arq);
  return (mat);
}
void printMatriz(char *nome, double **mat, int m, int n){
  puts(nome);
  for(int i=0; i<m; i++) {
    for(int j=0; j<n; j++){
      printf("%g\t", mat[i][j]);
    }
    puts("");
  }
}
void liberaMatriz(double** mat, int m){
  //liberar a memoria alocada pelo programa para armazenar a matriz
  for(int i=0; i<m; i++)
    free(mat[i]);
  free(mat);
}

//manipulacao de vetores
double* leVetor(char *nome, int *m){
  FILE* arq = fopen(nome, "rt");
  fscanf(arq, "%d\n", m);

  double* x = (double*)malloc((*m)*sizeof(double));
  for (int i=0; i<(*m); i++){
    fscanf(arq, "%lf", &x[i]);
  }

  return x;
}
void printVetor(char *nome, double *vet, int m){
  puts(nome);
  for(int i=0; i<m; i++)  printf("%g\t", vet[i]);
}
double* copyVet(double *vet, int m){
  double *copia = malloc(m*sizeof(double));
  for (int i=0; i<m; i++){
    copia[i] = vet[i];
  }
  return copia;
}
