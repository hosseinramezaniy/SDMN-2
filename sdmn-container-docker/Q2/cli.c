
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ftw.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
struct Arguments{
    int MaxMEM_Usage;
    char* hostname;
    int Nprocess;
};
typedef struct Arguments Arguments ; 
void CGroupEdit(Arguments* argument);
// Define the child function
int child_func(void* args) {
    Arguments *arg =  args ;
    char cmd[100];
    printf("openning new bash for the container.\nsupported commnads :cd , ls , mount , ps ,ip addr \n");
    printf("------------------------------------------------------------------------------------\n");
    char* rootdir = "/home/hossein/mn_HWs/HW2/sdmn-container-docker/Q2";
    int len = strlen(arg->hostname) ;
    chdir(rootdir);
    memset(cmd,0,100);
    sprintf(cmd,"chroot %s ./bin/bash --norc -c 'PS1=\"%s # \" bash'",rootdir,arg->hostname);
    system(cmd);
    // memset(cmd,0,100);
    // sprintf(cmd,"");
    system("umount proc");
    system("rm -r ./proc");
    printf("proc dir unmounted\n");
}

int main(int argc, char *argv[]) {
    Arguments *Args ;
    Args = (Arguments *)malloc(sizeof(Arguments));
    Args->hostname = argv[1] ;
    Args->MaxMEM_Usage = atoi(argv[2]);
    Args->Nprocess = atoi(argv[3]);
    const int STACK_SIZE = 1024*1024;
    char* stack = malloc(STACK_SIZE);
    if (!stack) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    CGroupEdit(Args);
    int flags = CLONE_NEWCGROUP | CLONE_NEWNET | CLONE_NEWPID | CLONE_NEWUTS | CLONE_NEWNS | SIGCHLD;
    pid_t pid = clone(child_func, stack + STACK_SIZE, flags, (void*)Args);
    if (pid == -1) {
        perror("clone failed");
        exit(EXIT_FAILURE);
    }
    // printf("Parent process\n");
    waitpid(pid, NULL, 0);
    free(stack);
    return 0;
}

void CGroupEdit(Arguments* argument){
    char* buff[4097];
    struct stat st = {0};

    if (stat("/sys/fs/cgroup/MyGroup", &st) == -1) {
        mkdir("/sys/fs/cgroup/MyGroup", 0777);
    }
    if (stat("./proc", &st) == -1) {
        mkdir("./proc", 0777);
    }
    char* procsAddr = "/sys/fs/cgroup/MyGroup/cgroup.procs" ;
    char* maxAddr = "/sys/fs/cgroup/MyGroup/memory.max" ;
    char* PIDMAddr = "/sys/fs/cgroup/MyGroup/pids.max" ;
    char buffer[10];
    realpath(procsAddr,buff);
    int f1 = open(procsAddr,O_WRONLY);

    sprintf(buffer,"%d",getpid());
    write(f1,&buffer, strlen(buffer));
    close(f1);
    memset(buff,0,4097);
    realpath(maxAddr,buff);
    int f2 = open(maxAddr,O_WRONLY);
    // fwrite(1024*1024*MaxM,sizeof(int),1,f);
    sprintf(buffer,"%d",1024*1024*argument->MaxMEM_Usage);
    write(f2,&buffer, strlen(buffer));
    close(f2);
    memset(buff,0,4097);
    realpath(PIDMAddr,buff);
    int f3 = open(PIDMAddr,O_WRONLY);
    // char c[1] =  ;
    memset(buffer,0,10);
    sprintf(buffer,"%d",argument->Nprocess);
    write(f3,buffer, strlen(buffer));
    // printf("xxx process %d , %d \n",f3);
    // printf("error:  %d \n",errno);
    close(f3);
}