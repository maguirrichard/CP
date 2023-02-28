/*
* Adapted from: http://w...content-available-to-author-only...s.org/sieve-of-eratosthenes
*
* Aluno: Maguirrichard Oliveira da Silva
*
* SEQUENCIAL
* real	0m2,693s
* user	0m2,639s
* sys	0m0,052s
*
*
* PARALELA
* real	0m2,245s -> speedup: 1,20
* user	0m7,276s
* sys	0m0,141s
*
*/

#include <omp.h>     
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
    

// Create a boolean array "prime[0..n]" and initialize
// all entries it as true. A value in prime[i] will
// finally be false if i is Not a prime, else true.
int sieveOfEratosthenes(int n) {
    int primes = 0; 
    bool *prime = (bool*) malloc((n+1)*sizeof(bool));
    int sqrt_n = sqrt(n);
	
    memset(prime, true,(n+1)*sizeof(bool));

	for (int p=2; p <= sqrt_n; p++)
	{
       	if (prime[p] == true) 
			#pragma omp parallel for
			for (int i=p*2; i<=n; i += p)
				prime[i] = false;
	}
     
    // count prime numbers
    #pragma omp parallel for
    for (int p=2; p<=n; p++)
       if (prime[p])
           primes++;
     
    return(primes);
}
     
int main() {
       int n = 100000000;
       printf("%d\n",sieveOfEratosthenes(n));
       return 0;
}
