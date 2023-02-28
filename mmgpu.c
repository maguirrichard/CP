/*
 * 
 * SEQUENCIAL:
 * real	1m22,872s
 * user	1m22,557s
 * sys	0m0,124s

 * PARALELA:
 * real	0m34,449s
 * user	2m15,194s
 * sys	0m0,068s
 * speedup -> 2,07

 * PARALELA (GPU):

 ** Distribute: 
 **  real	0m35,520s 
 **  user	2m16,257s
 **  sys	0m0,112s
 **  speedup -> 2,33
 
 ** Distribute parallel for: 
 **  real	0m40,026s 
 **  user	2m17,968s
 **  sys	0m0,524s
 **  speedup -> 2,07

 ** Distribute parallel for simd:
 **  real	0m33,740s 
 **  user	2m13,127s
 **  sys	0m0,096s
 **  speedup -> 2,45

 * Event result:
 * Event Name          Min         Max         Avg       Total
 * warps_launched      729072      729072      729072      729072

 * Metric result:
 * Metric Name                        Metric Description            Min         Max         Avg
 * warp_execution_efficiency          Warp Execution Efficiency     100.00%     100.00%     100.00%
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void mm(double* a, double* b, double* c, int width) 
{  
  int size = width * width;
  #pragma omp target map(to:a[:size]) map(to:b[:size]) map(tofrom:c[:size])        
  #pragma omp teams distribute //parallel for simd 
  //#pragma omp parallel for collapse(2) //- multicore
  for (int i = 0; i < width; i++) {        
    for (int j = 0; j < width; j++) {
      double   sum = 0;
      //#pragma omp simd //- multicore
      for (int k = 0; k < width; k++) {
        double x = a[i * width + k];
        double y = b[k * width + j];
        sum += x * y;
      }
      c[i * width + j] = sum;
    } 
  }
      
}

int main() {
  int width = 2000;
  double *a = (double*) malloc (width * width * sizeof(double));
  double *b = (double*) malloc (width * width * sizeof(double));
  double *c = (double*) malloc (width * width * sizeof(double));

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < width; j++) {
      a[i*width+j] = i;
      b[i*width+j] = j;
      c[i*width+j] = 0;
    }
  }

  mm(a,b,c,width);

  //  for(int i = 0; i < width; i++) {
  //  for(int j = 0; j < width; j++) {
  //    printf("\n c[%d][%d] = %f",i,j,c[i*width+j]);
  //  }
  // }
}
