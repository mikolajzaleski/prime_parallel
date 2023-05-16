#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include<unistd.h>
#include <math.h>
#include<string.h>
#include<fcntl.h>
void print_results(char* name,bool * primes_bool,unsigned long int min,unsigned long int max){
    FILE* x=fopen(name,"w+");
    fclose(x);   
    for (unsigned long int i = min;i<=max;i++){
    FILE* f=fopen(name,"a");    
       
        
        if(!primes_bool[i]){
            fprintf(f,"%ld\n",i);
        }
        fclose(f);
    }}
 int main( int argc, char *argv[])
{
    unsigned long int min = 2;
    unsigned long int max = 100000000;
    unsigned long int size = max - min;
    FILE f;
    bool prime = false;
    unsigned long int *primes;
    primes = malloc(sizeof(int) * size);
    unsigned long int num_primes = 0;
    bool * primes_bool;
    primes_bool=malloc(sizeof(bool)*(max + 1));
    //memset(primes_bool, true, sizeof(primes_bool))false;

    unsigned long int sqrt_sieve = sqrt(max);
    unsigned long int tmp; // temporary sum
    for (unsigned long int i = 2; i <= sqrt_sieve; i++)
    {
        if (primes_bool[i] == false)
        {
            for (tmp = i+i; tmp <= max; tmp += i)
            {
                primes_bool[tmp]=true;
                num_primes++;
            }
        }
    }

    print_results("name",primes_bool,min,max);
    printf("%ld",size);

}
