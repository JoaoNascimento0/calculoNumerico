#include <stdio.h>
#include <stdlib.h>

#include "Arrays.h"
#include "AlgLinear.h"
#include "Metodos.h"

int main(int argc, char** argv){  
  int m, n, it;
  double tol = 1e-8;

  puts("Questao 1.a --------------------------------");
  
  //leitura e alocacao de matriz.dat
  double** mat = leMatriz("questao1/matriz1a.dat", &m, &n);
    printMatriz("\nMatriz.", mat, m, n); 
  double *vet = leVetor("questao1/vetor1.dat", &m);  //vetor x0 referencia
    printVetor("\nx0: ", vet, m);

  //solucao por Gauss-Seidel.
  double *x0 = copyVet(vet, m);  //vetor auxiliar
  x0 = gaussSiedel(mat, m, n, x0, tol, &it);
    printVetor("\n\nRaizes Gauss-Siedel.", x0, m);
    printf("\nit: %d", it);

  //solucao por Gradiente.
  x0 = copyVet(vet, m);
  x0 = gradiente(mat, m, n, x0, 0, tol, &it);
    printVetor("\n\nRaizes Gradiente.", x0, m);
    printf("\nit: %d", it);

  //solucao por Gradiente COnjugado.
  x0 = copyVet(vet, m);
  x0 = GradienteConjugado(mat, m, n, x0, 0, tol, &it);
    printVetor("\n\nRaizes Gradiente Conjugado.", x0, m);
    printf("\nit: %d", it);

  puts("\n\nQuestao 1.b --------------------------------");

  mat = leMatriz("questao1/matriz1b.dat", &m, &n);
    printMatriz("\nMatriz.", mat, m, n);
    printVetor("\nx0: ", vet, m);

  //solucao por Gauss-Seidel.
  x0 = copyVet(vet, m);  //vetor auxiliar
  x0 = gaussSiedel(mat, m, n, x0, tol, &it);
    printVetor("\n\nRaizes Gauss-Siedel.", x0, m);
    printf("\nit: %d", it);

  //solucao por Gradiente.
  x0 = copyVet(vet, m);
  x0 = gradiente(mat, m, n, x0, 0, tol, &it);
    printVetor("\n\nRaizes Gradiente.", x0, m);
    printf("\nit: %d", it);

  //solucao por Gradiente COnjugado.
  x0 = copyVet(vet, m);
  x0 = GradienteConjugado(mat, m, n, x0, 0, tol, &it);
    printVetor("\n\nRaizes Gradiente Conjugado.", x0, m);
    printf("\nit: %d", it);
  
  //------------------------------------------------------//
  //comeco da segunda questao, aproveitando a memoria alocada antes.
  
  puts("\n\nQuestao 2 ----------------------------------");
  tol = 1e-3;  //definindo nova tolerancia
  
  mat = leMatriz("questao2/matriz2.dat", &m, &n);
    printMatriz("\nMatriz.", mat, m, n);
  
  vet = leVetor("questao2/vetor2.dat", &m);
    printVetor("\nVetor x0.", vet, m);

  //solucao por Gauss-Seidel.
  x0 = copyVet(vet, m);
  x0 = gaussSiedel(mat, m, n, x0, tol, &it);
    printVetor("\n\nRaizes Gauss-Siedel.", x0, m);
    printf("\nit: %d", it);
    printf("\n||x* - x(k)|| = %g", difVetor(x0, leVetor("questao2/SolucaoExata.dat", &m), m));

  //solucao por Gradiente.
  x0 = copyVet(vet, m);
  x0 = gradiente(mat, m, n, x0, 0, tol, &it);
    printVetor("\n\nRaizes Gradiente.", x0, m);
    printf("\nit: %d", it);
    printf("\n||x* - x(k)|| = %g", difVetor(x0, leVetor("questao2/SolucaoExata.dat", &m), m));

  //solucao por Gradiente COnjugado.
  x0 = copyVet(vet, m);
  x0 = GradienteConjugado(mat, m, n, x0, 0, tol, &it);
    printVetor("\n\nRaizes Gradiente Conjugado.", x0, m);
    printf("\nit: %d", it);
    printf("\n||x* - x(k)|| = %g", difVetor(x0, leVetor("questao2/SolucaoExata.dat", &m), m));

  
  liberaMatriz(mat, m);
  free(vet);
  free(x0);
  
  return 0;
}
