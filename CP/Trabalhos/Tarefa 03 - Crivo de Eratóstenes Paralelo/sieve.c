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

   memset(prime, true,(n+1)*sizeof(bool));
   //o parallel for nao é necessario aqui pois há uma dependencia de dados. Por exemplo os multiplos de 6 poderão ser excluidos antes dos multipos de 2 que são os de 6 também.
   for (int p=2; p <= sqrt_n; p++)
   {
       // If prime[p] is not changed, then it is a prime
       if (prime[p] == true)
       {
           // Update all multiples of p
			#pragma omp parallel for //excluir os multiplos em paralelo
           for (int i=p*2; i<=n; i += p)
           prime[i] = false;
        }
    }

    // count prime numbers
    #pragma omp parallel for reduction(+:primes) //incrementando a quantidade de numero primos 
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
   
	978283@PMG34INFLL20706:~/Downloads$ time ./sieve  // CODIGO SEQUENCIAL
	5761455

	real	0m1.705s
	user	0m1.677s
	sys		0m0.028s
	
	978283@PMG34INFLL20706:~/Downloads$ time ./sievePar // CODIGO EM PARALELO
	5761455

	real	0m1.030s
	user	0m3.950s
	sys		0m0.036s

	*/
   
   return 0;
} 
