#include <math.h>
#include <stdlib.h>

#include "AlgLinear.h"
#include "Arrays.h"

#include "Metodos.h"

//retorna um vetor de solucoes aproximada pela tolerancia 'tol'
double* gaussSiedel(double **mat, int m, int n, double *x, double tol, int *it){
  double dx, xant;
  *it=0;

  do{
    dx=0;
    for(int i=0; i<m; i++) {
      xant = x[i];
      x[i] = mat[i][m];
      for(int k=0; k<m; k++)
        if (k!=i) 
          x[i] -= mat[i][k]*x[k];
      x[i]/= mat[i][i];
      dx += fabs(x[i] - xant);
    }
    
    (*it)++;
  }while(dx>tol);

  return x;
}

//retorna um vetor de solucoes aproximada pela tolerancia 'tol'
double* gradiente(double **M, int m, int n, double *x, int p, double tol, int *it){
  double* xn = (double*)malloc(sizeof(double)*m);
  double* b = (double*)malloc(sizeof(double)*m);

  for (int i=0; i<m; i++)  b[i] = M[i][n-1];

  double* r0 = multiplicaVetorMatriz(M, m, x, m);
  r0 = ProdVetVet(1, b, -1, r0, m);

  double lbd, *r1;
  *(it) = 0;
  do{
    r1 = multiplicaVetorMatriz(M, m, r0, m);
    lbd = ProdutoInterno(r0, r0, m) / ProdutoInterno(r0, r1, m);

    xn = ProdVetVet(1, x, lbd, r0, m);

    r1 = multiplicaVetorMatriz(M, m, xn, m);
    r1 = ProdVetVet(1, b, -1, r1, m);

    for (int i=0; i<m; i++){  
      r0[i] = r1[i];
      x[i] = xn[i];
    }

    (*it)++;
  }while(normaVetor(r1, m, p) > tol);

  return x;
}

//retorna um vetor de solucoes aproximada pela tolerancia 'tol'
double* GradienteConjugado(double **M, int m, int n, double *x, int p, double tol, int *it){
  double *Ad, *Alpha, alpha, *r0, betha, prodi;

  double* b = (double*)malloc(m*sizeof(double));

  for (int i=0; i<m; i++){  
    b[i] = M[i][n-1];
  }

  r0 = multiplicaVetorMatriz(M, m, x, m);
  r0 = ProdVetVet(1, b, -1, r0, m);
  double* d0 = copyVet(r0, m);

  *(it) = 0;
  do{
    alpha = ProdutoInterno(r0, r0, m) /  ProdutoInterno(d0, multiplicaVetorMatriz(M, m, d0, m), m);

    for (int i=0; i<m; i++){
      x[i] += alpha * d0[i];
    }

    prodi = ProdutoInterno(r0, r0, m);
    double *aux = copyVet(r0, m);

    Ad = multiplicaVetorMatriz(M, m, d0, m);
    Alpha = VetorxEscalar(Ad, m, alpha);
    r0 = ProdVetVet(1, r0, -1, Alpha, m);

    betha = ((ProdutoInterno(r0, r0, m) / prodi));

    for (int i=0; i<m; i++){
      d0[i] = r0[i] + betha * d0[i];
    }

    (*it)++;
  } while (normaVetor(r0, m, p) > tol);

  return x;
}

