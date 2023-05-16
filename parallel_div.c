#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#define verboselist
// #define savelist

int main(int argc, char* argv[]){
    clock_t cstart, cend;
    double start, end;
   unsigned long int  min = 2;
   unsigned long int  max = 1000000;
   unsigned long int  size = max + 1 - min;

   unsigned long int  *primes;
    primes = malloc(sizeof(unsigned long int) * size);
   unsigned long int  num_primes = 0;

    if(min <= 2)
        primes[num_primes++] = 2;

    bool prime;

    cstart = clock();
    start = omp_get_wtime();

    #pragma omp parallel shared(num_primes) private(prime)
    #pragma omp for schedule(guided)
    for(unsigned long int i = min; i <= max; i++){
       unsigned long int  loc_max = (unsigned long int) ceil(sqrt(i));
        prime = true;

        for(unsigned long int j = 2; j <= loc_max; j++){
            if(i % j == 0){
                prime = false;
                break;
            }
        }

        #pragma omp critical (num_primes) 
        if(prime)
            primes[num_primes++] = i;
    } 
    
    cend = clock();
    end = omp_get_wtime();

    #ifdef verboselist
    for (unsigned long int i; i < num_primes; i++){
        printf("%-8d", primes[i]);
        if((i + 1) % 10 == 0)
            printf("\n");
    }
    printf("\n");
    #endif

    #ifdef savelist
    FILE *f = fopen("parallel_div.txt","w+");
    for (unsigned long int i = 0; i < num_primes; i++){
        fprintf(f,"%d\n",primes[i]);
    }
    fclose(f);
    #endif

    free(primes);

    printf("\nCzas procesora: %fs \nCzas przetwarzania: %fs\n%d liczb pierwszych\n", (double)(cend - cstart)/CLOCKS_PER_SEC, end - start, num_primes);

    return EXIT_SUCCESS;
}
