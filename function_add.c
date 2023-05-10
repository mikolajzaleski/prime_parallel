#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    unsigned long int max = 900000000;
    unsigned int size = max - min;
    unsigned int* start_p=create_start_primes(2,(int)(max)+1);

    // for(unsigned int i=1;i<start_p[0];i++){
    //     printf("%d ",start_p[i]);
    // }

    bool prime = false;
    int *primes;
    primes = malloc(sizeof(int) * size);
    int num_primes = 0;
    bool * primes_bool;
    primes_bool = malloc(sizeof(bool)*(max-min + 1));

    int thread_count;
     
    #pragma omp parallel
    thread_count = omp_get_num_threads();

    bool *primes_b=malloc(sizeof(bool)*(max));

    

    int sqrt_sieve = sqrt(max);
    int tmp; // temporary sum
    int i;
    cstart = clock();
    start = omp_get_wtime();
    

    #pragma omp parallel 
    {
        
        #pragma omp for schedule(dynamic)
        for(int i=0;i<start_p[0];i++){
            for (int j=start_p[i];j<max;j+=start_p[i]){
                if(j>min&&j!=start_p[i]){
                    primes_b[j]=true;
                }

            }
                
        }
       
    }
    
    
    cend = clock();
    end = omp_get_wtime();
    // #pragma omp for
    // for (unsigned long int  i=2;i<max;i++)
    //     if(!primes_b[i]){
    //         #pragma om
    //          num_primes+=1;
    //     // printf("%ld ",i);
    //     }
        // if(num_primes%50==0){
        //     printf("\n");
        // }
    printf("\n%d\n",num_primes);
        printf("\nCzas procesora: %fs \nCzas przetwarzania: %fs\n%d liczb pierwszych\n", (double)(cend - cstart)/CLOCKS_PER_SEC, end - start, num_primes);



    return(EXIT_SUCCESS);
}


unsigned int* create_start_primes(unsigned int min,unsigned int max){
    unsigned int* start_primes;
    unsigned long int num_primes=max;
    
    int idx=0;
    
    
    unsigned long int max_root=(unsigned long int)sqrt(max);
    start_primes=malloc(sizeof(unsigned long int)*max_root);
    bool* is_prime=malloc(sizeof(bool)*max_root);//valgrind pisze że tu się psuje
    for (int i=2;i<=max_root;i++){
        is_prime[i-2]=1;
    
    }
    for (int d=2;d<=max_root;d++){
        if(is_prime[d-2]==0)
            continue;
        for(int m=d+d;m<=max_root;m+=d){
            is_prime[m-2]=0;
        }

    }
    for (int i=min-2;i<max_root;i++){
        if(is_prime[i]==1)
            {   idx++;
                num_primes++;
            //    start_primes=(unsigned int*)realloc(start_primes,sizeof(unsigned int)*num_primes);
                start_primes[idx]=i+2;

            }       
    }
    start_primes[0]=idx+1;//size of array is stored  here
    free(is_prime);
    return start_primes;

}