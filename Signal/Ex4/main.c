#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sigstp(int sig);

int main(int argc, char *argv[]) 
{
    signal(SIGTSTP, handle_sigstp);

    while (1)
    {
        printf("Running...\n");
        sleep(1);
    }

    exit(0);
}

void handle_sigstp(int sig)
{
    if(sig == SIGTSTP)
    {
        printf("\nSIGTSTP ignored\n");
    }
}