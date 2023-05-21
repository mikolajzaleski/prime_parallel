#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include<stdint.h>
#include <time.h>
#include<omp.h>
#include <math.h>
#include<string.h>
#include<fcntl.h>
//#define PRINT_OPTIONS
uint64_t* create_start_primes(uint64_t max);

 int main( int argc, char *argv[])
{   clock_t cstart, cend;
    double start, end;
    cstart = clock();
    
    uint64_t min = 50;
    uint64_t max = 10000000000;
    uint64_t size = max - min;
    uint64_t* start_p=create_start_primes((uint64_t)(max)+1);

    bool prime = false;
    uint64_t *primes;
    primes = calloc(size,sizeof(int) );
    uint64_t num_primes = 0;
    bool * primes_bool;
    primes_bool=calloc((max -min),sizeof(bool));
    //memset(primes_bool, true, sizeof(primes_bool))false;
  
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
                        primes_bool[j-min]=true;
                    }
                   
                }
                

            }
                
        }
    for (uint64_t i=0 ;i<max-min;i++){
        if (!primes_bool[i])
            num_primes++;
            

    }
cend = clock();
    end = omp_get_wtime();
      #ifdef PRINT_OPTIONS     
       uint64_t num_druk=0;
        for(uint64_t i=0;i<=max-min;i++){
             if(!primes_bool[i])
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
    
    printf("\n%llu",num_primes);
        printf("\nCzas przetwarzania: %fs \n%llu liczb pierwszych\n", (double)(cend - cstart)/CLOCKS_PER_SEC,  num_primes);

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