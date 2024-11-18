#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Arrays.h"

//funcao manipulacao
void troca(double** a, double** b){
  double* temp = *a;
  *a = *b;
  *b = temp;
}

//funcao de matrizes
double** identidade(int m){
  double** mat = aloc(m, m);
  for(int i=0; i<m; i++)
    mat[i][i] = 1;  //corre na diagonal principal
  return mat;
}
void printMatriz(char* msg, double** mat, int m, int n){
  puts(msg);
  for(int i=0; i<m; i++){
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
double** aloc(int m, int n){
  //retorna uma matriz alocada 
  double** resp = malloc(m*sizeof(double*));
  for (int i=0; i<m; i++){
    resp[i] = malloc(n*sizeof(double));
  }
  return resp;
}
double** leMatriz(char* nome, int* m, int* n){
  FILE* arq = fopen(nome, "rt");

  //parametros de tamanho linha e coluna
  fscanf(arq, "%d %d\n", m, n);

  //alocacao da nova matriz
  double** mat = aloc((*m), (*n));

  //atribuicao de valores obtidos na matriz do arquivo.dat
  for(int i=0; i<(*m); i++){
    for(int j=0; j<(*n); j++){
      fscanf(arq, "%lf", &mat[i][j]);
    }
  }
  fclose(arq);
  return (mat);
}
double** multiplicaMatriz(double **A, int Am, int An, double **B, int Bm, int Bn){ 
  if(An!=Bm)
    puts("Erro na Multiplicacao.");

  double** resp = aloc(Am, Bn);

  //multiplica
  for(int i=0; i<Am; i++){
    for(int j=0; j<Bn; j++){
      resp[i][j] = 0;
      for(int k=0; k<An; k++)
        resp[i][j] += A[i][k]*B[k][j];
    }
  }
  return (resp);
}
double** SomaMatriz(double** M, int Am, int An, double a, double** N, int Bm, int Bn, double b){
  // Alocar memória para a matriz resultante
  double** resultado = aloc(Am, An);

  // Realizar a operação aM + bN
  for(int i=0; i<Am; i++){
    for(int j=0; j<An; j++){
      resultado[i][j] = (a*M[i][j]) + (b*N[i][j]);
    }
  }

  return resultado;
}
