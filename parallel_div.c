#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#include<stdint.h>

#define verboselist
// #define savelist

int main(int argc, char* argv[]){
    clock_t cstart, cend;
   double start, end;
   uint64_t  min = 2;
   uint64_t  max = 100;
   uint64_t  size = max + 1 - min;

   uint64_t  *primes;
   primes = calloc( size,sizeof(uint64_t) );
   uint64_t  num_primes = 0;

    if(min <= 2)
        primes[num_primes++] = 2;

    bool prime;

    cstart = clock();
    start = omp_get_wtime();

    #pragma omp parallel shared(num_primes) private(prime)
    #pragma omp for schedule(guided)
    for(uint64_t i = min; i <= max; i++){
       uint64_t  loc_max = (uint64_t) ceil(sqrt(i));
        prime = true;

        for(uint64_t j = 2; j <= loc_max; j++){
            if(i % j == 0){
                prime = false;
                break;
            }
        }

        #pragma omp critical (num_primes) 
        {
        if(prime){
            #pragma omp atomic
            num_primes++;
            primes[num_primes] = i;
    } }}
    
    cend = clock();
    end = omp_get_wtime();

    #ifdef verboselist
    for (uint64_t i; i < num_primes; i++){
        printf("%-8llu ", primes[i]);
        if((i + 1) % 10 == 0)
            printf("\n");
    }
    printf("\n");
    #endif

    #ifdef savelist
    FILE *f = fopen("parallel_div.txt","w+");
    for (uint64_t i = 0; i < num_primes; i++){
        fprintf(f,"%d\n",primes[i]);
    }
    fclose(f);
    #endif

    free(primes);

    printf("\nCzas procesora: %fs \nCzas przetwarzania: %fs\n%llu liczb pierwszych\n", (double)(cend - cstart)/CLOCKS_PER_SEC, end - start, num_primes);

    return EXIT_SUCCESS;
}
