#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc,char** argv){
    int arry[500];
    int p[2];
    int index = 0;
    for (int i = 2; i < 500; i++)
    {
        arry[index++] = i;
    }
    
    
    while(index > 0){
        pipe(p);
        int pid = fork();
        if (pid > 0){
            close(p[0]);
            for(int i = 0;i <= index;i++){
                write(p[1],&arry[i],4);
            } 
            close(p[1]);
            //wait for all child procress exit;
            wait(0);
            exit(0);  
        }else if(pid == 0){
            int temp = 0;
            int primes = 0;
            index = -1;
            close(p[1]);
            while(read(p[0],&temp,4) != 0){
                if (index >= 0)
                {
                    if(temp % primes != 0) arry[index++] = temp;
                }else{
                    primes = temp;
                    index++;
                }
            }
            printf("prime %d\n",primes);
            close(p[0]);
        }else{
            fprintf(2,"fork() error");
            exit(1);
        }   
    }
    exit(0);
}
