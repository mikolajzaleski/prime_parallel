#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<omp.h>
#define shortlist
// #define verboselist
//#define wer2
#define wer1
int main(int argc,char* argv[]){
    int min =2;
    int max=10000001;
    int size=max-min;
    bool prime=false;
    int  *primes;
    primes=malloc(sizeof(int)*size);
    int num_primes=1;
    
    int cur=1;
    primes[0]=2;
    #pragma omp parallel shared(num_primes)
    {

      #pragma omp for schedule(guided,3) reduction(+:num_primes)
        for(int i=min;i<=max;i++){
        
        int loc_max=sqrt(i)+1;
        bool prime=false;
        #ifdef wer1 
        for(int j=2;j<=loc_max;j++){
            
            if(i%j==0){
                prime=false;
                break; 
            }else{
                prime=true;
         }   
        }
        #endif
        #ifdef wer2
        for(int y=0;y<num_primes;y++){
              if(i%primes[y]==0){
                prime=false;
                break; 
            }else{
                prime=true;
         }   
        }
        #endif
        if(prime){
        
        primes[num_primes]=i;
       
        num_primes++;
        
    }
    }
    } 
    #ifdef verboselist
    for (int i=0;i<num_primes;i++){
        printf("%d ",primes[i]);
    }
    #endif
      
    //   FILE * f=fopen("seq_div.txt","w");
    //   fclose(f);
    //   for (int i=0;i<num_primes;i++){
    //   f=fopen("seq_div.txt","a");
    //   fprintf(f,"%d\n",primes[i]);
    //   fclose(f);
    //   }
      free(primes);
#ifdef shortlist
printf("W zakresie od %d do %d wykryto %d liczb pierwszych \n",min,max,num_primes);

#endif
}