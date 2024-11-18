#include <math.h>
#include <stdlib.h>

#include "Arrays.h"

//rotinas de matrizes.
double* multiplicaVetorMatriz(double **M, int m, double *x, int n) {
  double *y = calloc(n, sizeof(double));

  for (int i=0; i<m; i++){
    for (int j=0; j<n; j++){
      y[i] += M[i][j] * x[j];
    }
  }
  return y;
}

//rotina de vetores.
double normaVetor(double* vet, int m, int p){
  double norma=0, maior=0;

  if(p){
    for(int i=0; i<m; i++)
      norma+= pow(fabs(vet[i]),p);
    norma = pow(norma, 1./p);
  }
  else{
    for(int i=0; i<m; i++){
      maior = fabs(vet[i]);
      norma = (maior>norma) ?  maior:norma;
    }
  }
  return norma;
}
double ProdutoInterno(double *x, double *y, int m){
  double prod = 0;

  for (int i=0; i<m; i++)
    prod += x[i] * y[i];

  return prod;
}
double* ProdVetVet(double lbd1, double *x1, double lbd2, double *x2, int m){
  double *vet = (double*)malloc(m*sizeof(double));

  for (int i=0; i<m; i++)
    vet[i] = lbd1*x1[i] + lbd2*x2[i];

  return vet;
}
double* VetorxEscalar(double *v, int n, double k){
  int i;
  double *aux1;
  aux1 = calloc(k, sizeof(double));
  aux1 = v;

  for (i = 0; i < n; i++)
    aux1[i] = k * aux1[i];

  return aux1;
}
double difVetor(double* a, double* b, int m){
  for(int i=0; i<m; i++)  a[i] -= b[i];
  return normaVetor(a, m, 0);  
}

