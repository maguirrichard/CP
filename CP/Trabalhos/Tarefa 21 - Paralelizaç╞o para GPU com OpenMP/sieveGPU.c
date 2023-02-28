/*
* Adapted from: http://w...content-available-to-author-only...s.org/sieve-of-eratosthenes
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int sieveOfEratosthenes(int n)
{
   // Create a boolean array "prime[0..n]" and initialize
   // all entries it as true. A value in prime[i] will
   // finally be false if i is Not a prime, else true.   
   int primes = 0;
   bool *prime = (bool*) malloc((n+1)*sizeof(bool));
   int sqrt_n = sqrt(n);
   int p, i = 0;

   memset(prime, true,(n+1)*sizeof(bool));
   //o parallel for nao Ã© necessario aqui pois hÃ¡ uma dependencia de dados. Por exemplo os multiplos de 6 poderÃ£o ser excluidos antes dos multipos de 2 que sÃ£o os de 6 tambÃ.mm
   #pragma omp target map(tofrom:prime[0:n+1])
   #pragma omp teams distribute parallel for simd
    for (p=2; p <= sqrt_n; p++)
   {
       // If prime[p] is not changed, then it is a prime
       if (prime[p] == true)
       {
           // Update all multiples of
        for (i=p*2; i<=n; i += p){
           prime[i] = false;
           }

        }
    }

    // count prime number
    #pragma omp target map(tofrom:primes) map(to:prime[0:n+1])
    #pragma omp teams distribute parallel for simd reduction(+:primes)
    for (int p=2; p<=n; p++){
       if (prime[p]){
         primes += 1;
         }
         }


    return(primes);
}

int main()
{
   int n = 100000000;
   printf("%d\n",sieveOfEratosthenes(n));

   /*
   Tempo sequencial: 4.008s
   Tempo paralelo: 3.013s
   Tempo paralelo com GPU: 3.138s
   */

   return 0;
}
