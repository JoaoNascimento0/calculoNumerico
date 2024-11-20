#include <math.h>
#include <stdio.h>

#define Y 0.009 // 9 mm ou 0.009 m
#define L 3.0   // 3 m
#define E 70.0  // 70 Gpa
//#define I 52.9 * pow(-6, 10) //52.9 m^4
#define Wo 15.0 // 15 kN/m

double f(float x) // funcao ta certa
{
  double termo1, termo2,
      I = 52.9 * (pow(10, -6)); // dividido para entender melhor

  termo1 = ((Wo * L) / (3 * pow(M_PI, 4) * E * I)); // correto

  termo2 = (48 * pow(L, 3) * cos(((M_PI) / (2 * L) * x)) - (48 * pow(L, 3)) +
            3 * pow(M_PI, 3) * L * pow(x, 2) - pow(M_PI, 3) * pow(x, 3));

  return (termo1 * termo2);
}

double df(float x) // derivada da funcao
{
  double termo1, termo2, I = 52.9 * (pow(10, -6));

  termo1 = ((Wo * L) / (3 * pow(M_PI, 4) * E * I));

  termo2 =
      ((-93.0188) * pow(x, 2) + (558.1129 * x - 678.58401 * sin(0.52359 * x)));

  return (termo1 * termo2);
}

double bissecao(double a, double b, double tolerancia, int i) {
  int cont = 0; // contador de interacoes
  double x0, c; // valor medio

  c = a - b;
  x0 = (a + b) / 2.0;

  while (c > tolerancia || fabs(f(x0)) > tolerancia) { // enquanto...faça
    if ((f(a) * f(x0)) < 0.00) {
      b = x0;
    }
    if ((f(a) * f(x0)) > 0.00) {
      a = x0;
    }

    c = b - a;
    x0 = (a + b) / 2.0;

    cont++;          // numeros de interacoes
    if (cont >= i) { // se cont for o numero de interacoes for maior que o
                     // limite...break
      break;
    }
  }

  printf("Metodo Bissecao:\nf(x) da raiz: %lf\tInteracoes: %d", f(x0),
         cont); // printando resultado
}

void regula_falsi(double a, double b, double tolerancia, int i) {
  int cont = 0; // contador de interacoes
  double x0, c; // valores medios

  c = b - a;
  x0 = (a * f(b)) - (b * f(a) / f(b)) - f(a); // aproximacao

  while (c > tolerancia) {
    if (f(a) * f(x0) < 0.00) {
      b = x0;
    }
    if (f(a) * f(x0) > 0.00) {
      a = x0;
    }
    c = b - a;
    x0 = ((a * f(b)) - (b * f(a) / f(b)) - f(a));

    if (cont >= i || fabs(f(x0)) <= tolerancia) {
      break;
    }
  }
  printf("\n\nMetodo Regula-Falsi\nf(x) da raiz: %lf\tInteracoes: %d\n", f(x0),
         cont); // printando resultado
}

void newton(double a, double b, double tolerancia, double i) {
  int cont = 0; // contador de interacoes
  double x0, c; // valor medio

  while (fabs(f(x0)) > tolerancia) {

    c = x0 - f(x0) / df(x0); // calculo para aproximacao
    x0 = c;

    cont++;
    if (cont >= i) {
      break;
    }
  }
  printf("\nMetodo de Newton\nf(x) da raiz: %lf\tInteracoes: %d\n", f(x0),
         cont); // printando resultado
}

void secante(double a, double b, double tolerancia, int i) {
  int cont = 0, n = 0; // contador para acessar os valores do vetor
  int x[100];          // vetor usado para organizar os valores de aproximacao
  double x0, c;

  x[0] = a;
  x[1] = b;

  while (fabs(f(x0)) > tolerancia) {

    x[n + 1] = ((x[n] - (x[n] - x[n - 1]) / (f(x[n]) - f(x[n - 1])) * f(x[n])));

    cont++; // contador de interacoes
    n++;    // contador para o vetor
    if (cont >= i) {
      break; // condicao de parada
    }
  }
  printf("\nMetodo de secate\nf(x) da raiz: %lf\tInteracoes: %d\n", f(x[n]),
         cont); // printando resultado
}

int main(void) {
  int i = 1000; // numero limite de vezes que o while roda
  double a, b;
  double tolerancia =
      (Y + pow(10, -6)); // temos que encontrar o ponto aonde y = 0,009 m
  // double tolerancia = pow(10, -6);

  a = 0.0460; // valores de entrada
  b = 0.0468; // valores de entrada

  bissecao(a, b, tolerancia, i);     // chamada da funcao bissecao
  regula_falsi(a, b, tolerancia, i); // chamada da funcao regula_falsi
  newton(a, b, tolerancia, i);       // chamada da funcao de newton
  secante(a, b, tolerancia, i);      // chamada da funcao secante

  return 0;
}