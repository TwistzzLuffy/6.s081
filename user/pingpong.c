#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char const *argv[])
{
	int p[2]; // store pips descriptions (parent -> child) p[0] | p[1]
	int p1[2]; //store pips2 descriptions (child -> parent)
	char buf[1];
	pipe(p);
	pipe(p1);
	int pid = fork();
	if(pid < 0){
		fprintf(2,"fork() error\n");
		close(p[0]);
		close(p[1]);
		close(p1[0]);
		close(p1[1]);
		exit(1);
	}
	if(pid == 0){						
		close(p[1]);
		close(p1[0]);
		if(read(p[0],buf,sizeof(buf)) != 1){
			fprintf(2,"faild to read in child");
			exit(1);
		}else{
			printf("%d: received ping\n",getpid());	
		}
		if(write(p1[1],"h",1) != 1){
			fprintf(2,"faild to write in child");
			exit(1);			
		}
		close(p[0]);
		close(p1[1]);
		exit(0);
	}else{
		close(p1[1]);
		close(p[0]);
		if(write(p[1],"e",1) != 1){
			fprintf(2,"faild to write in parent");
			exit(1);
		}
		wait(0);
		if(read(p1[0],buf,sizeof(buf)) != 1){
			fprintf(2,"faild to read in parent");
			exit(1);
		}else{
			printf("%d: received pong\n",getpid());
		}
		close(p[1]);
		close(p1[0]);
		exit(0);
	}
	return 0;
}
