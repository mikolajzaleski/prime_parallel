#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
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
    for(int i=min;i<=max;i++){
        int loc_max=sqrt(i)+1;
        prime=false;
        for(int j=2;j<=loc_max;j++){
            
            if(i%j==0){
                prime=false;
                break; 
            }else{
                prime=true;
         }   
        }
        if(prime){
        primes[num_primes]=i;
       
        num_primes++;
    }
   
    } 
    for (int i=0;i<num_primes;i++){
        printf("%d ",primes[i]);
    }
    
      
      FILE * f=fopen("seq_div.txt","w");
      fclose(f);
      for (int i=0;i<num_primes;i++){
      f=fopen("seq_div.txt","a");
      fprintf(f,"%d\n",primes[i]);
      fclose(f);
      }
      free(primes);


}