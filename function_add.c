#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<stdint.h>


#include <math.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <fcntl.h>
#define START_NUMBER 10000
#define PARTITION_SIZE sizeof(bool)*((max-min)/thread_count+1)

uint64_t* create_start_primes(uint64_t max);
int main(int argc, char *argv[])
{omp_set_num_threads(8);
    clock_t cstart, cend;
    double start, end;
    unsigned int min = 2;
    uint64_t max = 100ULL;
    uint64_t size = max - min;
    uint64_t* start_p=create_start_primes((uint64_t)(max)+1);

    // for(unsigned int i=1;i<start_p[0];i++){
    //     printf("%d ",start_p[i]);
    // }

    bool prime = false;
    int *primes;
    primes = malloc(sizeof(int) * size);
    uint64_t num_primes = 0;
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
        for(uint64_t i=0;i<start_p[0];i++){
            for (uint64_t j=start_p[i];j<=max;j+=start_p[i]){
                if(j>min&&j!=start_p[i]){
                    primes_b[j-min]=true;
                }

            }
                
        }
       
    }
    
    
    cend = clock();
    end = omp_get_wtime();
    uint64_t nump=0;
    #pragma omp parallel for schedule(guided)
    for(uint64_t i=0;i<=max;i++){
	
    if(!primes_b[i])
	{
	//	primes[idx]=i;
    #pragma omp atomic
        	nump++;
//        printf("%d ",i);
	}
    }
    // #pragma omp for
    // for (uint64_t  i=2;i<max;i++)
    //     if(!primes_b[i]){
    //         #pragma om
    //          num_primes+=1;
    //     // printf("%llu ",i);
    //     }
        // if(num_primes%50==0){
        //     printf("\n");
        // }
	//
	num_primes=nump+1;
    printf("\n%llu\n",num_primes);
        printf("\nCzas procesora: %fs \nCzas przetwarzania: %fs\n%llu liczb pierwszych\n", (double)(cend - cstart)/CLOCKS_PER_SEC, end - start, num_primes);



    return(EXIT_SUCCESS);
}


uint64_t* create_start_primes(uint64_t max){
    uint64_t* start_primes;
    uint64_t min=2;
    uint64_t num_primes=max;
    
    uint64_t idx=0;
    
    
    uint64_t max_root=(uint64_t)sqrt(max);
    start_primes=malloc(sizeof(uint64_t)*max_root);
    bool* is_prime=malloc(sizeof(bool)*max_root);//valgrind pisze że tu się psuje
    for (uint64_t i=2;i<=max_root;i++){
        is_prime[i-2]=1;
    
    }
    for (uint64_t d=2;d<=max_root;d++){
        if(is_prime[d-2]==0)
            continue;
        for(uint64_t m=d+d;m<=max_root;m+=d){
            is_prime[m-2]=0;
        }

    }
    for (uint64_t i=min-2;i<max_root;i++){
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