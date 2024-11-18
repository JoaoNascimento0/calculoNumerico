#include <stdio.h>

//abriga todas as rotinas de leitura e print de arrays
#include "Arrays.h"

//abriga todas as rotinas para os metodos
#include "AlgLinear.h"

int main(int argc, char **argv){
  int m, n;

  if(!argv[1]){
    puts("\nargv[1] vazio!.\n");
    return -1;
  }

  //double** M = leMatriz("exemplos/matriz5x5.dat", &m, &n);
  double** M = leMatriz(argv[1], &m, &n);
  printMatriz("\nEntrada.", M, m, n);
  
  double** W = inversa(M, m, n);
  printMatriz("\nInversa.", W, m, m);
  
  double** C = multiplicaMatriz(M, m, m, W, m, m);
  printMatriz("\nProva.", C, m, m);
  
  C = SomaMatriz(C, m, m, 1, identidade(m), m, m, -1);
  
  printf("\nResiduos = %g\n", residuo(C, m, m, 2));

  liberaMatriz(M, m);
  liberaMatriz(W, m);
  liberaMatriz(C, m);
  return 0;
}

/*  Algoritmo:
M = LeMatriz (argv[1], &m, &n);
W = Inversa(M, m, m) ;
ImprimeMatriz("Inversa", W, m, m);

C = MultiplicaMatriz(M,m,m,W,m,m);
C = SomaMatriz(C,m,m,1,Identidade(m), m,m, -1);

printf("Resíduos= %lf\n", NormaMatriz(C,2));
*/