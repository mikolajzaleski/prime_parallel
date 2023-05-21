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
   uint64_t  max = 400000000;
   
   uint64_t  size = max + 1 - min;

   bool  *primes;
   primes = calloc( size,sizeof(bool) );
   uint64_t  num_primes = 0;

    
    bool prime;

    cstart = clock();
    start = omp_get_wtime();

   
    for(uint64_t i = min; i <= max; i++){
       uint64_t  loc_max = (uint64_t) ceil(sqrt(i));
        prime = true;

        for(uint64_t j = 2; j <= loc_max; j++){
            if(i % j == 0){
                prime = false;
                break;
            }
        }

       
        if(prime){
            num_primes++;
            primes[i-min] = true;
    }}
    
    cend = clock();
    end = omp_get_wtime();

    #ifdef verboselist
    uint64_t lc=0;
    for (uint64_t i=0; i < (max-min); i++){
        if(primes[i]){
            lc++;
        printf("%llu ", i+min);
        if((lc) % 10 == 0)
            printf("\n");
    }}
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
