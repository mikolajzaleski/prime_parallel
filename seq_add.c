#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include<unistd.h>
#include <math.h>
#include<string.h>
#include<fcntl.h>
void print_results(char* name,bool * primes_bool,int min,int max){
    FILE* x=fopen(name,"w+");
    fclose(x);   
    for (int i = min;i<=max;i++){
    FILE* f=fopen(name,"a");    
       
        
        if(primes_bool[i]){
            fprintf(f,"%d\n",i);
        }
        fclose(f);
    }}
int main(int argc, char *argv[])
{
    int min = 2;
    int max = 100000001;
    int size = max - min;
    FILE f;
    bool prime = false;
    int *primes;
    primes = malloc(sizeof(int) * size);
    int num_primes = 0;
    bool primes_bool[max + 1];
    memset(primes_bool, true, sizeof(primes_bool));

    int sqrt_sieve = sqrt(max);
    int tmp; // temporary sum
    for (int i = 2; i <= sqrt_sieve; i++)
    {
        if (primes_bool[i] == true)
        {
            for (tmp = i+i; tmp <= max; tmp += i)
            {
                primes_bool[tmp]=false;
            }
        }
    }

    print_results("name",primes_bool,min,max);
}
