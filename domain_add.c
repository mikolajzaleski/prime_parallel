#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <unistd.h>
#include <math.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <fcntl.h>
#define START_NUMBER 10000
#define PARTITION_SIZE sizeof(bool)*((max-min)/thread_count+1)

unsigned int* create_start_primes(unsigned int min,unsigned  int max);
int main(int argc, char *argv[])
{
    clock_t cstart, cend;
    double start, end;
    unsigned int min = 3;
    unsigned int max = 300000;
    unsigned int size = max - min;
    unsigned int* start_p=create_start_primes(2,(int)sqrt(max)+1);

    for(unsigned int i=1;i<start_p[0];i++){
        printf("%d ",start_p[i]);
    }

    bool prime = false;
    int *primes;
    primes = malloc(sizeof(int) * size);
    int num_primes = 0;
    bool * primes_bool;
    primes_bool = malloc(sizeof(bool)*(max-min + 1));

    int thread_count;
     
    #pragma omp parallel
    thread_count = omp_get_num_threads();

    bool **subsets=malloc(sizeof(bool*)*thread_count);

    for(int i = 0; i < thread_count; ++i)
        subsets[i] = malloc(PARTITION_SIZE);

    int sqrt_sieve = sqrt(max);
    int tmp; // temporary sum
    int i;
    cstart = clock();
    start = omp_get_wtime();
    

    #pragma omp parallel 
    {
        int thread_num = omp_get_thread_num();
        bool *p_subset = subsets[thread_num];
        unsigned int lower_l = (int)((max-min)/(thread_count)) * thread_num;
        unsigned int upper_l = (int)(((max-min)/(thread_count))) * (thread_num + 1) - 1;
        for (int i=1;i<start_p[0];i++){//size of array is stored  here start_p[0]
            int min_m=lower_l/start_p[i];
            
           
           for(int j=min_m*start_p[i];j<upper_l;j+=start_p[i]){
            int ix=j-lower_l;
            if (j!=start_p[i])
            {subsets[thread_num][ix]=true;}
      //     printf("%d \n",j);
           }
        }

 
    }
    for (int i=0;i<thread_count;i++){
        for (int j=2;j<(int)((max-min)/(thread_count));j++){
            if(subsets[i][j]==false){
                printf("%d \n",j+((max-min)/(thread_count))*i);
            }
        }
    }
    cend = clock();
    end = omp_get_wtime();
    for (int i=2;i<max;i++)
        if(!primes_bool[i]) num_primes+=1;

    printf("\n%d\n",num_primes);
        printf("\nCzas procesora: %fs \nCzas przetwarzania: %fs\n%d liczb pierwszych\n", (double)(cend - cstart)/CLOCKS_PER_SEC, end - start, num_primes);

    free(primes_bool);
    for(int i = 0; i < thread_count; ++i)
        free(subsets[i]);

    return(EXIT_SUCCESS);
}


unsigned int* create_start_primes(unsigned int min,unsigned int max){
    unsigned int* start_primes;
    int num_primes=10000;
    
    int idx=0;
    start_primes=malloc(sizeof(unsigned int)*num_primes);
    
    int max_root=(int)sqrt(max);
    bool* is_prime=malloc(sizeof(bool)*START_NUMBER);
    for (int i=2;i<=max;i++){
        is_prime[i-2]=1;
    
    }
    for (int d=2;d<=max_root;d++){
        if(is_prime[d-2]==0)
            continue;
        for(int m=d+d;m<=max;m+=d){
            is_prime[m-2]=0;
        }

    }
    for (int i=min-2;i<max;i++){
        if(is_prime[i]==1)
            {   idx++;
                num_primes++;
                start_primes=(unsigned int*)realloc(start_primes,sizeof(unsigned int)*num_primes);
                start_primes[idx]=i+2;

            }
            
    }
    start_primes[0]=idx+1;//size of array is stored  here
    free(is_prime);
    return start_primes;

}