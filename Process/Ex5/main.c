#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    pid_t pid_zombie = fork();
    if (pid_zombie < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid_zombie == 0) //child process
    {   
        printf("I'm child process (zombie) with pid = %d\n", getpid());
        exit(100); //if parent does not call wait() function child process will become zombie process
    }

    pid_t pid_orphan = fork();
    if (pid_orphan < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid_orphan == 0)
    {
        sleep(1);
        printf("I'm child process (orphan) with pid = %d and ppid = %d\n", getpid(), getppid()); 
        sleep(15); //if parent process exit before child process, child process will become orphan process
        printf("I'm child process (orphan) with pid = %d and new ppid = %d\n", getpid(), getppid());  
    }

    sleep(10); //sleep to check zombie process in terminal and parent process exit before child process (< 15)
    printf("Parent exited!\n");

    return 0;
}
