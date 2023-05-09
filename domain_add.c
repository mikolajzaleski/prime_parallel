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
#define PARTITION_SIZE sizeof(bool)*(max-min/8+1)

unsigned int* create_start_primes(unsigned int min,unsigned  int max);
int main(int argc, char *argv[])
{
    clock_t cstart, cend;
    double start, end;
    unsigned int min = 2;
    unsigned int max = 300000000;
    unsigned int size = max - min;
    unsigned int* start_p=create_start_primes(3,10000);
    for(unsigned int i=1;i<start_p[0];i++){
        printf("%d ",start_p[i]);
    }
    bool prime = false;
    int *primes;
    primes = malloc(sizeof(int) * size);
    int num_primes = 0;
    bool * primes_bool;
    primes_bool = malloc(sizeof(bool)*(max-min + 1));
    
    bool *subset1, *subset2, *subset3, *subset4, *subset5, *subset6, *subset7, *subset8;
    subset1=malloc(PARTITION_SIZE);
    subset2=malloc(PARTITION_SIZE);
    subset3=malloc(PARTITION_SIZE);
    subset4=malloc(PARTITION_SIZE);
    subset5=malloc(PARTITION_SIZE);
    subset6=malloc(PARTITION_SIZE);
    subset7=malloc(PARTITION_SIZE);
    subset8=malloc(PARTITION_SIZE);
    bool *subsets[]={subset1,subset2,subset3,subset4,subset5,subset6,subset7,subset8};
    

    int sqrt_sieve = sqrt(max);
    int tmp; // temporary sum
    int i;
    cstart = clock();
    start = omp_get_wtime();
    

    #pragma omp parallel shared(i)
    for ( i = 2; i <= sqrt_sieve; i++)
    {
        if (primes_bool[i] == false)
        {
            #pragma omp parallel for schedule(guided,1) 
            for (tmp = i+i; tmp < max; tmp += (i))
            {
                primes_bool[tmp]=true;
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
    free(subset1);
    free(subset2);
    free(subset3);
    free(subset4);
    free(subset5);
    free(subset6);
    free(subset7);
    free(subset8);

    return(EXIT_SUCCESS);
}
unsigned int* create_start_primes(unsigned int min,unsigned int max){
    unsigned int* start_primes;
    int num_primes=10;
    
    int idx=0;
    start_primes=malloc(sizeof(int)*num_primes);
    
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