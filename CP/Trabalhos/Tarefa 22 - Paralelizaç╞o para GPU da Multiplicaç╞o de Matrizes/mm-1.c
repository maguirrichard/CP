/*
Tempo sequencial: 1m6.924s
Tempo paralelo para multicore: 0m36.802s
Tempo paralelo GPU somente com distribute: 0m48.446s
Tempo paralelo GPU distribute parallel for: 0m9.356s
Tempo paralelo GPU distribute parallel for simd : 0m5.457s

METRICAS DO NVPROF PARA GPU distribute
==9592== Event result:
Invocations                                Event Name         Min         Max         Avg       Total
Device "GeForce GT 1030 (0)"
    Kernel: mm$_omp_fn$0
          1                            warps_launched          72          72          72          72

==9592== Metric result:
Invocations                               Metric Name                        Metric Description         Min         Max         Avg
Device "GeForce GT 1030 (0)"
    Kernel: mm$_omp_fn$0
          1                 warp_execution_efficiency                 Warp Execution Efficiency      98.33%      98.33%      98.33%
		  
 ****************************************************************************************************************************************
		  
METRICAS DO NVPROF PARA GPU distribute parallel for
==9475== Event result:
Invocations                                Event Name         Min         Max         Avg       Total
Device "GeForce GT 1030 (0)"
    Kernel: mm$_omp_fn$0
          1                            warps_launched          72          72          72          72

==9475== Metric result:
Invocations                               Metric Name                        Metric Description         Min         Max         Avg
Device "GeForce GT 1030 (0)"
    Kernel: mm$_omp_fn$0
          1                 warp_execution_efficiency                 Warp Execution Efficiency     100.00%     100.00%     100.00%		  
	
 ****************************************************************************************************************************************
 
METRICAS DO NVPROF PARA GPU distribute parallel for simd
==9245== Event result:
Invocations                                Event Name         Min         Max         Avg       Total
Device "GeForce GT 1030 (0)"
    Kernel: mm$_omp_fn$0
          1                            warps_launched          72          72          72          72

==9245== Metric result:
Invocations                               Metric Name                        Metric Description         Min         Max         Avg
Device "GeForce GT 1030 (0)"
    Kernel: mm$_omp_fn$0
          1                 warp_execution_efficiency                 Warp Execution Efficiency      86.81%      86.81%      86.81%

 ****************************************************************************************************************************************
	
*/

#include <stdio.h>
#include <stdlib.h>

void mm(double* a, double* b, double* c, int width)
{
  //#pragma omp target map(to:a[0:(width*width)], b[0:(width*width)]) map(from:c[0:(width*width)])
  //#pragma omp teams distribute parallel for simd
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      double sum = 0;
      //#pragma omp parallel for reduction(+:sum)
      for (int k = 0; k < width; k++) {
        double x = a[i * width + k];
        double y = b[k * width + j];
        sum += x * y;
      }
      c[i * width + j] = sum;
    }
  }
}

int main()
{
  int width = 2000;
  double *a = (double*) malloc (width * width * sizeof(double));
  double *b = (double*) malloc (width * width * sizeof(double));
  double *c = (double*) malloc (width * width * sizeof(double));
  
  //#pragma omp parallel for collapse(2)
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
