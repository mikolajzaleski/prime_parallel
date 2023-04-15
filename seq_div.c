#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#define verboselist
// #define savelist

int main(int argc,char* argv[]){
    clock_t cstart, cend;
    double start, end;
    int min = 2;
    int max = 10000000;
    int size = max + 1 - min;

    int *primes;
    primes = malloc(sizeof(int) * size);
    int num_primes = 0;

    if(min <= 2)
        primes[num_primes++] = 2;

    bool prime;

    cstart = clock();
    start = omp_get_wtime();

    for(int i = min; i <= max; i++){
        int loc_max = (int) ceil(sqrt(i));
        prime = true;

        for(int j = 2; j <= loc_max; j++){
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
    for (int i; i < num_primes; i++){
        printf("%-8d", primes[i]);
        if((i + 1) % 10 == 0)
            printf("\n");
    }
    printf("\n");
    #endif

    #ifdef savelist
    FILE *f = fopen("seq_div.txt","w+");
    for (int i = 0; i < num_primes; i++){
        fprintf(f,"%d\n",primes[i]);
    }
    fclose(f);
    #endif

    free(primes);

    printf("\nCzas procesora: %fs \nCzas przetwarzania: %fs\n%d liczb pierwszych\n", (double)(cend - cstart)/CLOCKS_PER_SEC, end - start, num_primes);

    return EXIT_SUCCESS;
}
