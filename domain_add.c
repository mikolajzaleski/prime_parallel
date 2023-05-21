#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <fcntl.h>

#define PARTITION_SIZE (sizeof(bool) * (uint64_t)ceil((max - min) / thread_count))
#define loud
// #define numbers
uint64_t *create_start_primes(uint64_t max);

int main(int argc, char *argv[])
{   omp_set_num_threads(14);
    // init
    clock_t cstart, cend;
    double start, end;
 cstart = clock();
    start = omp_get_wtime();
    uint64_t num_primes = 0;

    uint64_t min = 50;
    uint64_t max = 10000000000;

    uint64_t size = max - min;
    uint64_t *start_primes = create_start_primes((max));

    // num of threads
    int thread_count;
#pragma omp parallel
    thread_count = omp_get_num_threads();
#ifdef loud
    printf("\n%d threads found!\n\n", thread_count);
#endif

    // initialize subset for each thread
    bool **subsets = malloc(sizeof(bool *) * thread_count);
    for (int i = 0; i < thread_count - 1; ++i)
        subsets[i] = malloc(PARTITION_SIZE);
    subsets[thread_count - 1] = malloc(size - ((thread_count - 2) * PARTITION_SIZE));
    // start ticking ;)
   

    // after init

#pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        bool *subset = subsets[thread_num];
        uint64_t lower_bound = min + PARTITION_SIZE * thread_num;
        uint64_t upper_bound = (thread_num + 1 == thread_count) ? max : min + PARTITION_SIZE * (thread_num + 1) - 1;

#ifdef loud
        printf("T%-3d from %-12llu to %llu\n", thread_num, lower_bound, upper_bound);
#endif

        uint64_t start_primes_count = start_primes[0];
        for (uint64_t i = 1; i < start_primes_count; ++i)
        {
            uint64_t iterator = 0;
            uint64_t mul_occurence;
            while (lower_bound + iterator <= upper_bound)
            {
                if ((lower_bound + iterator) % start_primes[i] == 0)
                {
                    mul_occurence = lower_bound + iterator;
                    break;
                }
                else
                    iterator++;
            }
            while (mul_occurence <= upper_bound)
            {
                if (mul_occurence != start_primes[i])
                    subset[iterator] = true;
                iterator += start_primes[i];
                mul_occurence += start_primes[i];
            }
        }
    }

 
#pragma omp parallel for schedule(guided)
    for (uint64_t i = 0; i <= size; ++i)
    {
        uint64_t subset_idx = i / PARTITION_SIZE;
        uint64_t element_idx = i % PARTITION_SIZE;
        if (subsets[(subset_idx >= thread_count - 1) ? thread_count - 1 : subset_idx][(subset_idx >= thread_count) ? i - (thread_count - 1) * PARTITION_SIZE : element_idx] == false)
        {

#pragma omp atomic
                num_primes++;
           
#ifdef numbers
            printf("%d\n", ((subset_idx >= thread_count - 1) ? thread_count - 1 : subset_idx) * PARTITION_SIZE + min + ((subset_idx >= thread_count) ? i - (thread_count - 1) * PARTITION_SIZE : element_idx));
#endif
        }
    }
    #pragma omp barrier
   cend = clock();
    end = omp_get_wtime();
    printf("%llu \n",num_primes);
    printf("\nCzas procesora: %fs \nCzas przetwarzania: %fs\n%llu liczb pierwszych\n", (double)(cend - cstart) / CLOCKS_PER_SEC, end - start, num_primes);

    for (int i = 0; i < thread_count; ++i)
        free(subsets[i]);

    return EXIT_SUCCESS;
}

uint64_t *create_start_primes(uint64_t max)
{
    uint64_t *start_primes;
    uint64_t min = 2;
    uint64_t num_primes = max;

    uint64_t idx = 0;

    uint64_t max_root = (uint64_t)sqrt(max);
    start_primes = malloc(sizeof(uint64_t) * max_root);
    bool *is_prime = malloc(sizeof(bool) * max_root); // valgrind pisze że tu się psuje
    for (uint64_t i = 2; i <= max_root; i++)
    {
        is_prime[i - 2] = 1;
    }
    for (uint64_t d = 2; d <= max_root; d++)
    {
        if (is_prime[d - 2] == 0)
            continue;
        for (uint64_t m = d + d; m <= max_root; m += d)
        {
            is_prime[m - 2] = 0;
        }
    }
    for (uint64_t i = min - 2; i < max_root; i++)
    {
        if (is_prime[i] == 1)
        {
            idx++;
            num_primes++;
            //    start_primes=(unsigned int*)realloc(start_primes,sizeof(unsigned int)*num_primes);
            start_primes[idx] = i + 2;
        }
    }
    start_primes[0] = idx + 1; // size of array is stored  here
    free(is_prime);
    return start_primes;
}
