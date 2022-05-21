#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXMEM 1024

int main(int argc,char **argv){
    if(argc > MAXARG){
        fprintf(2,"xargs : arg is too much \n");
        exit(1);
    }

    char *param[MAXARG];
    char mem[MAXMEM];
    int param_argc = 0;
    char *cmd = argv[1];
    int n;
    for (int i = 1; i < argc; ++i)
        param[param_argc++] = argv[i];
    int pid = fork();
    if(pid == 0){
        int index = 0;
        char *arg = (char *)malloc(sizeof(char));
       
        while((n = read(0,mem,MAXMEM)) > 0){
            for(int i = 0; i < n;i++){
                if(mem[i] == ' ' || mem[i] == '\n'){
                    arg[index] = 0;
                    printf("%s\n", arg);
                    index = 0;
                    param[param_argc++] = arg;
                    arg =(char *)malloc(sizeof(char));
                }else{
                    arg[index++] = mem[i]; 
                }
            }
        }
        exec(cmd,param);
    }else if(pid > 0){
        wait(0);
    }else{
        fprintf(2,"fork() error\n");
        exit(1);
    }
    exit(0);
}