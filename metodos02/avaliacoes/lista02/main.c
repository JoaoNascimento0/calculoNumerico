#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//funcao que recebe os vetores e anota seus valores em um arquivo *p
void grava(FILE *p, double* x, double* resp, int iter, int m){
  fprintf(p ,"\n%d\t", iter);
  for(int i=0; i<m; i++)
    fprintf(p, "%g\t\t", fabs(x[i]-resp[i]));
}

//manipulacao de arrrays
double** leMatriz(char* nome, int* m, int* n){
  FILE* arq = fopen(nome, "rt");

  //parametros de tamanho linha e coluna
  fscanf(arq, "%d %d\n", m, n);

  //alocacao da nova matriz
  double** newMat = malloc((*m)*sizeof(double*));
  for(int i=0; i<(*m);i++)
    newMat[i] = malloc((*n)*sizeof(double*));

  //atribuicao de valores obtidos na matriz do arquivo.dat
  for(int i=0; i<(*m); i++)
    for(int j=0; j<(*n); j++){
      fscanf(arq, "%lf", &newMat[i][j]);
    }

  fclose(arq);
  return (newMat);
}
double* leVetor(char* nome, int* tam){
  FILE* arq = fopen(nome, "rt");
  double *NovoVetor;
  
  fscanf(arq, "%d\n", tam);

  //alocacao do novo vetor
  NovoVetor = malloc((*tam)*sizeof(double*));

  //atribuicao de valores obtidos na matriz do arquivo.dat
  for(int i=0; i<(*tam); i++)
      fscanf(arq, "%lf", &NovoVetor[i]);

  fclose(arq);
  return (NovoVetor);
}
void liberaMatriz(double** mat, int m, int n){
  for (int i=0; i<m; i++) 
    free (mat[i]); 
  free (mat);
}
void printMatriz(char* texto, double** Mat, int m, int n){
  puts(texto);

  for(int i=0; i<m; i++){
    for(int j=0; j<n; j++){
      printf("%g\t\t", Mat[i][j]);
    }
    printf("\n");
  }
}
void printVetor(char* texto, double* vet, int m){
  puts(texto);
  for(int i=0; i<m; i++)  
    printf("%g\t\t", vet[i]);
  puts("");
}

//metodos iterativos customizados para atender as demandas dos exercicios, ao inves de retornar as raizes temos aqui rotinas void e gravando o vetor X_i a cada iteracao.
void jacobi(char* nome, double **M, double* x, double* resp, int m, int n, double tol){
  FILE* arq = fopen(nome, "wt");
  int it=0;
  double dx;

  double *xt = malloc(m*sizeof(double)); 
  
  do{
    dx=0;
    for(int i=0; i<m; i++){
      xt[i] = M[i][m]; 
      for(int k=0; k<m; k++){
        if (k!=i) 
          xt[i] -= M[i][k]*x[k];
      }
      xt[i]/= M[i][i];
      
      dx += fabs(x[i] - xt[i]);
    }
    memcpy(x, xt, m*sizeof(double));
    it++;

    grava(arq, x, resp, it, m);
    
  } while(dx>tol);
  
  free(xt);
}
void gauss(char *nome, double **M, double* x, double* resp, int m, int n, double tol){
  int it=0;
  double dx, xant;
  FILE* arq = fopen(nome, "wt");

  do{
    dx=0;
    for(int i=0; i<m; i++){
      xant = x[i];
      x[i] = M[i][m];
      for(int k=0; k<m; k++)
        if (k!=i) 
          x[i] -= M[i][k]*x[k];
      
      x[i]/= M[i][i];
      dx += fabs(x[i] - xant);
    }
    it++;  
    grava(arq, x, resp, it, m);
    
  }while(dx>tol);

  fclose(arq);
}


int main(int argc, char** argv){
  int lin, col;                 //dimensoes
  double tol = 1e-7;            //tolerancia
  double resp[] = {3, 4, -5};   //respostas exatas para comparacao

  double** mat = leMatriz("matriz.dat", &lin, &col);
  //double** mat = leMatriz(argv[1], &lin, &col);
  
  double x0[3] = {0.0};         //chute inicial
  gauss("gaussResult.dat", mat, x0, resp, lin, col, tol);

  double x1[3] = {0.0};         //chute inicial
  jacobi("JacobiResult.dat", mat, x1, resp, lin, col, tol);
  
  liberaMatriz(mat, lin, col);
  
  return 0;
}
