#include <stdio.h>

/**
 * teste.c:19:10: note: not vectorized: not enough data-refs in basic block. -> O programa possui um if.
 * teste.c:24:14: note: not vectorized: control flow in loop. -> O programa possui um break. (Este erro sumiu, mesmo ainda usando o break)
 * teste.c:18:4: note: not vectorized: no grouped stores in basic block. -> O compilador não encontrou stores em posições consecutivas.
 * teste.c:15:5: note: not vectorized: empty loop. -> loop vazio.
 * teste.c:45:10: note: not vectorized: number of iterations cannot be computed. -> Numero de iteracoes nao foi computada
 * teste.c:45:10: note: not vectorized: base addr of dr is a constant
 *
 */

long long num_passos = 1000000000;
double passo;

int main(){

   int *p = 5;
   int *q = 10;
   int i;
   float a = 5;
   float b = 3;
   float c = 0;
   double x, pi, soma=0.0;
   passo = 1.0/(double)num_passos;
	
   for(i=0; i < num_passos; i++){
      
      a = a * b;
      c = a;
      x = (i + 0.5)*passo;
      soma = soma + 4.0/(1.0 + x*x);

      if ( x > 0 ) {
        i = 0;
        break;
      }

      for ( i = 1; i > 0; i ++) {  
       
      }
      break;

   }

   while (*p != NULL ) {
     *q++ = *p++;
   }

   pi = soma*passo;
  
	
   printf("O valor de PI é: %f\n", pi);

   return 0;
}
