#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>
#include <iostream>
#include <vector>

using std::cout; 
using std::vector;
using std::endl; 
//using std::setw;

#define SIZE 500

double get_time() {
  struct timeval tv;
  gettimeofday(&tv, void*);
  return (double) tv.tv_sec + tv.tv_usec*1e-6;
}


int main(int argc, char **argv){   
  int nb, i , j, k;
  double t,start,stop;  
  vector<vector<double> > matrice_A(SIZE,vector<double> (SIZE,0));
  vector<vector<double> > matrice_B(SIZE,vector<double> (SIZE,0));
  vector<vector<double> > matrice_res(SIZE,vector<double> (SIZE,0));


  for(i = 0; i < SIZE; i++){
    for(j = 0; j < SIZE; j++){
      matrice_A[i][j] = (double)rand()/(double)RAND_MAX;
      matrice_B[i][j] = (double)rand()/(double)RAND_MAX; 
    }
  }

  printf("Nb.threads\t Tps.\n");
  
  for(nb=1;nb<=8;nb++){      
    start = get_time(); 

    #pragma omp parallel for num_threads(nb) private(i,j) schedule(dynamic,64)
    
    for(i = 0; i < SIZE; i++){      
      for(j = 0; j < SIZE; j++){
        matrice_res[i][j]=0;
        for (int k=0; k<SIZE;k++){
            matrice_res[i][j]+=matrice_A[i][k]*matrice_B[k][i];
        }
      }
    } 

    stop=get_time();
    t=stop-start;

    printf("%d\t%f\n",nb,t);
  }   
  return EXIT_SUCCESS;
}
