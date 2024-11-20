//codigo de diferencas finitas usando decomposicao LU e algoritmo de crout

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// y'' + y' + cos(x)

// y(x) = −1/10*(sin(x) + 3 cos(x))

double f(double x, double y, double yl){
   return (- 1/10*(sin(x) + 3*cos(x))); 
}
double fl(double x, double y, double yl){ // df/dy
    return (1/10*(sin(x) - 3*cos(x)));
}
double fll(double x, double y, double yl){ // df/dy'
    return (1/10*(cos(x) + 3*cos(x)));
}

double *DiferencaFinita(double a, double b, int N, double h, double alpha, double beta){
    int i, itera;
    double x, t, h2 , yl, norma;
    double *D, *U, *L, *R, *y, *l, *u, *v, *z;
    
    h2 = h*h; 


    D = malloc((N+2)*sizeof (double));
    L = malloc((N+2)*sizeof (double));
    U = malloc((N+2)*sizeof (double));
    R = malloc((N+2)*sizeof (double));
    
    l = malloc((N+1)*sizeof (double));
    u = malloc((N+1)*sizeof (double));
    y = malloc((N+2)*sizeof (double));
    v = malloc((N+2)*sizeof (double));
    z = malloc((N+2)*sizeof (double));
    
    
    for(i=1; i<=N; i++) 
      y[i] = alpha + i*h*(beta - alpha)/(b - a);
    
    y[0] = alpha;
    y[N+1] = beta;
    
    itera = 0;
    do 
    {
        t = a + h;
        yl = (y[2] - alpha)/(2*h);
        //primeiro coeficiente de cada vetor          
        D[1] = 2 + h2*fl(t,y[1],yl);
        U[1] = -1 + (h/2)*fll(x,y[1],yl);
        R[1] = -(2*y[1] - y[2] - alpha + h2*f(t,y[1],yl));
        
        //coeficientes "do meio"
        for(i=2; i<N; i++){
          t = a + i*h;
          yl = (y[i+1] - y[i-1])/(2*h); 
          D[i] = 2 + h2*fl(t,y[i],yl); 
          U[i] = -1 + (h/2)*fll(t,y[i],yl);
          L[i] = -1 - (h/2)*fll(t,y[i],yl);
          R[i] = -(-y[i-1] + 2*y[i] - y[i+1] + h2*f(t,y[i],yl));
        }
        
        t = b-h;
        yl = (beta - y[N-1])/(2*h);

        //último coeficiente de cada vetor     
        D[N] = 2 + h2*fl(t,y[N],yl);
        L[N] = -1 - (h/2)*fll(t,y[N],yl);
        R[N] = -(2*y[N] - y[N-1] - beta + h2*f(t,y[N],yl));
        
        //Método de Croutz
        l[1] = D[1];
        u[1] = U[1]/D[1];
        z[1] = R[1]/l[1];
        
        for(i=2; i<N; i++){
          l[i] = D[i] - L[i]*u[i-1];
          u[i] = U[i]/l[i];
          z[i] = (R[i] - L[i]*z[i-1])/l[i];
        }
        
        l[N] = D[N] - L[N]*u[N-1];
        z[N] = (R[N] - L[N]*z[N-1])/l[N];
        v[N] = z[N];
        y[N] += v[N];
        norma = 0;
         
        for(i=N-1; i>0; i--){   
          v[i] = z[i] - u[i]*v[i + 1];
          if(fabs(v[i])>norma) 
            norma = fabs(v[i]);
          y[i] += v[i];
        }
        itera++;
    }while((norma > 1e-8));  
    return y;
}

//função para calcular o erro dos valores obtidos
void *Erro(double *x, double alpha, double beta, int N, double a, double h){
    int j;
    double *s;
    FILE *arq;

    arq = fopen("dados100.dat", "w");
    s = malloc((N+2)*sizeof (double));

    //erro do primeiro valor
    /*s[0] = fabs(alpha - 0);

    //erro dos valores "do meio"
    for(j=1; j<=N; j++)
      s[j] = fabs((x[j]) - log(a+j*h));

    //erro do último valor
    s[N] = fabs(beta - log(a+N*h));*/

    for(j=0; j<N+2; j++)
      fprintf(arq, "%g %g \n", a+j*h, /*s*/x[j]);
}

/*
a = extremidade inicial do intervalo
b = extremidade final do intervalo
N = número de elementos dentro do intervalo
alpha, beta = condições iniciais
h = tamanho do passo
x = vetor resultado
*/

int main(int argc, char **argv){
  int N, i;
  double  *x, *y, a, b, h, t, alpha, beta;
  FILE *arq;

  a = 0;
  b = (M_PI/2.0);
  
  N = 100;
  h = (b-a)/(N+1);
  
  alpha = -0.3;
  beta = -0.1; 
    
  x = DiferencaFinita(a, b, N, h, alpha, beta);
  Erro (x, alpha, beta, N, a, h);

  return 0;
}
