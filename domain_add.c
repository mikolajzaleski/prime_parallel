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

    int sqrt_sieve = sqrt(max);
    int tmp; // temporary sum
    int i;
    cstart = clock();
    start = omp_get_wtime();
    #pragma omp parallel shared(i) 
    {
    #pragma omp parallel for schedule(guided,1)
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
}
