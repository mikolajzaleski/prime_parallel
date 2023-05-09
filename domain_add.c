#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include<unistd.h>
#include <math.h>
#include<string.h>
#include<omp.h>
#include<time.h>
#include<fcntl.h>
int main(int argc, char *argv[])
{
    clock_t cstart, cend;
    double start, end;
    unsigned int min = 2;
    unsigned int max = 300000000;
    unsigned int size = max - min;
    FILE f;
    bool prime = false;
    int *primes;
    primes = malloc(sizeof(int) * size);
    int num_primes = 0;
    bool * primes_bool;
    primes_bool=malloc(sizeof(bool)*(max + 1));
    //memset(primes_bool, true, sizeof(primes_bool))false;
    bool *subset1;
    bool *subset2;
    bool *subset3;
    bool *subset4;
    bool *subset5;
    bool *subset6;
    bool *subset7;
    bool *subset8;
    subset1=malloc(sizeof(bool)*(max/8+1));
    subset2=malloc(sizeof(bool)*(max/8+1));
    subset3=malloc(sizeof(bool)*(max/8+1));
    subset4=malloc(sizeof(bool)*(max/8+1));
    subset5=malloc(sizeof(bool)*(max/8+1));
    subset6=malloc(sizeof(bool)*(max/8+1));
    subset7=malloc(sizeof(bool)*(max/8+1));
    subset8=malloc(sizeof(bool)*(max/8+1));
    bool *subsets[]={subset1,subset2,subset3,subset4,subset5,subset6,subset7,subset8};
    subsets[0][1]=1;

    int sqrt_sieve = sqrt(max);
    int tmp; // temporary sum
    int i;
    cstart = clock();
    start = omp_get_wtime();
    

    #pragma omp parallel shared(i) 
    {
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
    }
    
    cend = clock();
    end = omp_get_wtime();
    for (int i=2;i<max;i++){
        if(!primes_bool[i]) num_primes+=1;

    }
    printf("%d\n",num_primes);
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
    
}
