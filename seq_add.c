#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include<stdint.h>

#include <math.h>
#include<string.h>
#include<fcntl.h>

 int main( int argc, char *argv[])
{
    uint64_t min = 2;
    uint64_t max = 500000000;
    uint64_t size = max - min;
  
    bool prime = false;
    uint64_t *primes;
    primes = malloc(sizeof(int) * size);
    uint64_t num_primes = 0;
    bool * primes_bool;
    primes_bool=malloc(sizeof(bool)*(max + 1));
    //memset(primes_bool, true, sizeof(primes_bool))false;

    uint64_t sqrt_sieve = sqrt(max);
    uint64_t tmp; // temporary sum
    for (uint64_t i = 2; i <= sqrt_sieve; i++)
    {
        if (primes_bool[i] == false)
        {
            for (tmp = i+i; tmp <= max; tmp += i)
            {
                primes_bool[tmp]=true;
                
            }
        }
    }
    for (uint64_t i=2 ;i<max;i++){
        if (!primes_bool[i])
            num_primes++;
            

    }

    
    printf("%llu",num_primes);

}
