#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>

pid_t pid1;
pid_t pid2;
pid_t wpid1;
pid_t wpid2;
int fd[2];
char buf[50];
int count;

void child1(){
     while(1){
        sprintf(buf,"I send you %d times!\n",count);
        write(fd[1],buf,50);
        count++;
        sleep(1);
     }

}

void child2(){
    while(1){
        read(fd[0],buf,50);
        printf("%s",buf);
    }

}

void killAll(){
    printf("The first process is killed!\n");
    kill(pid1,SIGKILL);
    
    printf("The second process is killed!\n");
    kill(pid2,SIGKILL);
}


int main(){
    signal(SIGINT,killAll);
    pipe(fd);

    if(!(pid1 = fork())) child1();
    if(!(pid2 = fork())) child2();

    //if (pid1 && pid2) {
        do {
            if (wpid1 != pid1) {
                wpid1 = waitpid(pid1, NULL, WNOHANG);
            }
            
            if (wpid2 != pid2) {
                wpid2 = waitpid(pid2, NULL, WNOHANG);
            }
            
        } while (wpid1 != pid1 || wpid2 != pid2);
    //}
    
    close(fd[0]);
    close(fd[1]);
}


