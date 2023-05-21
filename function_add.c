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
//#define PRINT_OPTIONS
uint64_t* create_start_primes(uint64_t max);
int main(int argc, char *argv[])
{  // omp_set_num_threads(14);
     uint64_t nump=0;
    clock_t cstart, cend;
    double start, end;
    cstart = clock();
    start = omp_get_wtime(); 
    
    uint64_t min = 50;
    uint64_t max = 10000000000;
    uint64_t size = max - min;
    uint64_t* start_p=create_start_primes((uint64_t)(max)+1);

    // for(unsigned int i=1;i<start_p[0];i++){
    //     printf("%d ",start_p[i]);
    // }

    bool prime = false;
    int *primes;
    uint64_t num_primes = 0;
    bool * primes_bool;

    int thread_count;
     
    #pragma omp parallel
    thread_count = omp_get_num_threads();
     
    bool *primes_b=(bool*)calloc((max-min+1),sizeof(bool));
  

    int sqrt_sieve = sqrt(max);
    int tmp; // temporary sum
    int i;
   nump=0;
//for (int row=0;row<15;row++){#define 
 #pragma omp parallel 
 {
        #pragma omp  for schedule(dynamic)
        for(uint64_t i=1;i<start_p[0];i++){
            uint64_t mn=min%start_p[i];
            //uint64_t start_n=min-mn+start_p[i];
            uint64_t start_n=min-mn;
            // if(start_n<0){
            //     start_n=0;
            // }
            for (uint64_t j=start_n;j<=max;j+=start_p[i]){
                if(j!=start_p[i]){
                    if ((j>=min)){
                        primes_b[j-min]=true;
                    }
                   
                }
                

            }
                
        }
 // }     

    
    
     
   //  #pragma omp parallel
     //{
    #pragma omp  for schedule(guided)
    for(uint64_t i=0;i<=max-min;i++){
	
    if(!primes_b[i])
	{
	//	primes[idx]=i;
    #pragma omp atomic
        	nump++;
  
	}
    
    }
    
}cend = clock();
    end = omp_get_wtime();
    
      #ifdef PRINT_OPTIONS     
       uint64_t num_druk=0;
        for(uint64_t i=0;i<=max-min;i++){
             if(!primes_b[i])
	{
        printf("%lu ",i+min);
        num_druk++;
       // #pragma omp critical 
        // {

            if(num_druk%10==0)
                printf("\n");
        // } 
        }
        }
     #endif
    //}    // #pragma omp for
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
	
    printf("\n%llu\n",nump);
        printf("\nCzas procesora: %fs \nCzas przetwarzania: %fs\n%llu liczb pierwszych\n", (double)(cend - cstart)/CLOCKS_PER_SEC, end - start, nump);
   // free(primes_b);


    return(EXIT_SUCCESS);
}


uint64_t* create_start_primes(uint64_t max){
    uint64_t* start_primes;
    uint64_t min=2;
    uint64_t num_primes=max;
    
    uint64_t idx=0;
    
    
    uint64_t max_root=(uint64_t)sqrt(max);
    start_primes=calloc(max_root,sizeof(uint64_t));
    bool* is_prime=calloc(max_root,sizeof(bool));//valgrind pisze że tu się psuje
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