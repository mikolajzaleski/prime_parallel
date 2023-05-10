#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
#include <math.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <fcntl.h>
 
#define PARTITION_SIZE (sizeof(bool) * (int)ceil((max-min)/thread_count))
#define loud
 
unsigned int* create_start_primes(unsigned int max);
 
int main(int argc, char *argv[])
{   omp_set_num_threads(8); 
    //init
    clock_t cstart, cend;
    double start, end;
 
    int num_primes = 0;
 
    int min = 2;
    int max = 1000000000;
    int size = max - min;
    unsigned int* start_primes = create_start_primes((max));
 
    //num of threads
    int thread_count;
    #pragma omp parallel
    thread_count = omp_get_num_threads();
    #ifdef loud
    printf("\n%d threads found!\n\n", thread_count);
    #endif
 
    //initialize subset for each thread
    bool **subsets=malloc(sizeof(bool*)*thread_count);
    for(int i = 0; i < thread_count - 1; ++i)
        subsets[i] = malloc(PARTITION_SIZE);
    subsets[thread_count - 1] = malloc(size - ((thread_count - 2)* PARTITION_SIZE));
    //start ticking ;)
    cstart = clock();
    start = omp_get_wtime();
 
    // after init
    #pragma omp parallel 
    {
        int thread_num = omp_get_thread_num();
        bool *subset = subsets[thread_num];
        int lower_bound = min + PARTITION_SIZE * thread_num;
        int upper_bound = (thread_num + 1 == thread_count)? max : min + PARTITION_SIZE * (thread_num + 1) - 1;
 
        #ifdef loud
        printf("T%-3d from %-12d to %d\n",thread_num,lower_bound,upper_bound);
        #endif
 
        int start_primes_count = start_primes[0];
        for(int i = 1; i < start_primes_count; ++i){
            int iterator = 0;
            int mul_occurence;
            while(lower_bound + iterator <= upper_bound){
                if((lower_bound + iterator) % start_primes[i] == 0){
                    mul_occurence = lower_bound + iterator;
                    break;
                }
                else
                    iterator++;
            }
            while(mul_occurence <= upper_bound){
                if(mul_occurence != start_primes[i])
                    subset[iterator] = true;
                iterator += start_primes[i];
                mul_occurence += start_primes[i];
            }
        }
    }
 
    cend = clock();
    end = omp_get_wtime();
 
    // for (int i=0;i<thread_count;i++){
    //     for (int j=0;j<(int)((max-min)/(thread_count));j++){
    //         if(subsets[i][j]==false){
    //             printf("%d \n",j+((max-min)/(thread_count))*i);
    //         }
    //     }
    // }
    // for(int i = 0; i <= size; ++i){
    //     int subset_idx = i / PARTITION_SIZE;
    //     int element_idx = i % PARTITION_SIZE;
    //     if(subsets[(subset_idx >= thread_count - 1)? thread_count - 1 : subset_idx][(subset_idx >= thread_count)? i - (thread_count - 1) * PARTITION_SIZE : element_idx] == false){
    //         num_primes++;
    //         #ifdef loud
 
    //         #endif
    //     }
    // }
 
    printf("\nCzas procesora: %fs \nCzas przetwarzania: %fs\n%d liczb pierwszych\n", (double)(cend - cstart)/CLOCKS_PER_SEC, end - start, num_primes);
 
    for(int i = 0; i < thread_count; ++i)
        free(subsets[i]);
 
    return(EXIT_SUCCESS);
}
 
// int* create_start_primes(int sqrt_of_max){
 
//     primes = malloc(sizeof(int) * sqrt_of_max);
 
//     bool* is_prime=malloc(sizeof(bool)*max_root);
 
//     for (int i=2;i<=max;i++){
//         is_prime[i-2]=1;
 
//     }
//     for (int d=2;d<=max_root;d++){
//         if(is_prime[d-2]==0)
//             continue;
//         for(int m=d+d;m<=max;m+=d){
//             is_prime[m-2]=0;
//         }
 
//     }
//     for (int i=min-2;i<max;i++){
//         if(is_prime[i]==1)
//             {   idx++;
//                 num_primes++;
//             //    start_primes=(unsigned int*)realloc(start_primes,sizeof(unsigned int)*num_primes);
//                 start_primes[idx]=i+2;
 
//             }       
//     }
//     start_primes[0]=idx+1;//size of array is stored  here
//     free(is_prime);
//     return start_primes;
// }
unsigned int* create_start_primes(unsigned int max){
    unsigned int* start_primes;
    unsigned int min=2;
    unsigned long int num_primes=max;
    
    int idx=0;
    
    
    unsigned long int max_root=(unsigned long int)sqrt(max);
    start_primes=malloc(sizeof(unsigned long int)*max_root);
    bool* is_prime=malloc(sizeof(bool)*max_root);//valgrind pisze że tu się psuje
    for (int i=2;i<=max_root;i++){
        is_prime[i-2]=1;
    
    }
    for (int d=2;d<=max_root;d++){
        if(is_prime[d-2]==0)
            continue;
        for(int m=d+d;m<=max_root;m+=d){
            is_prime[m-2]=0;
        }

    }
    for (int i=min-2;i<max_root;i++){
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