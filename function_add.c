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

unsigned long int* create_start_primes(unsigned long  int max);
int main(int argc, char *argv[])
{unsigned long int num_primes=0;
	//omp_set_num_threads(8);
    clock_t cstart, cend;
    double start, end;
    unsigned int min = 400000000;
    unsigned long int max = 4000000000;
    unsigned long int size = max - min;
    unsigned long int* start_p=create_start_primes((unsigned long int)(max)+1);

    // for(unsigned int i=1;i<start_p[0];i++){
    //     printf("%d ",start_p[i]);
    // }
   bool prime = false;
    unsigned long int *primes;
    primes = malloc(sizeof(unsigned long int) * size/3);
    num_primes = 0;
    

    int thread_count;
     
    #pragma omp parallel
    thread_count = omp_get_num_threads();

    bool *primes_b=malloc(sizeof(bool)*(max+1));

    unsigned long int idx=0;

    unsigned long  int sqrt_sieve = sqrt(max)+1;
    unsigned long int tmp; // temporary sum
    unsigned long int i;
    cstart = clock();
    start = omp_get_wtime();
    

    #pragma omp parallel 
    {
        
        #pragma omp for 
        for(int i=0;i<start_p[0];i++){
            for (int j=start_p[i];j<=max;j+=start_p[i]){
                if(j>min&&j!=start_p[i]){
                    primes_b[j]=true;
                }

            }
                
        }
       
    }

    
    cend = clock();
    end = omp_get_wtime();
    for(unsigned long int i=2;i<=max;i++){
	if(!primes_b[i])
	{
	//	primes[idx]=i;
		idx++;
//        printf("%d ",i);
	}
    }
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
	//
	num_primes=idx+1;
    printf("\n%d\n",num_primes);
        printf("\nCzas procesora: %fs \nCzas przetwarzania: %fs\n%ld liczb pierwszych\n", (double)(cend - cstart)/CLOCKS_PER_SEC, end - start, num_primes);



    return(EXIT_SUCCESS);
}

 
unsigned long int* create_start_primes(unsigned long int max){
    unsigned long int* start_primes;
    unsigned int min=2;
    unsigned long int num_primes=max;
    
    int idx=0;
    
    
    unsigned long int max_root=(unsigned long int)sqrt(max);
    start_primes=malloc(sizeof(unsigned long int)*max_root);
    bool* is_prime=malloc(sizeof(bool)*max_root);//valgrind pisze że tu się psuje
    for (unsigned long int i=2;i<=max_root;i++){
        is_prime[i-2]=1;
    
    }
    for (unsigned long int d=2;d<=max_root;d++){
        if(is_prime[d-2]==0)
            continue;
        for(unsigned long int m=d+d;m<=max_root;m+=d){
            is_prime[m-2]=0;
        }

    }
    for (unsigned long int i=min-2;i<max_root;i++){
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
