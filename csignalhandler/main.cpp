#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int time_to_quit;
int stop_count;

void sig_handler(int signum)
{
    switch(signum)
    {
    case SIGUSR1:
        printf("...received SIGUSR1...\n");
        break;
    case SIGUSR2:
        printf("...received SIGUSR2...\n");
        break;
    case SIGHUP:
        printf("...received SIGHUP...\n");
        break;
    case SIGCONT:
        printf("...received SIGCONT...\n");
        stop_count = 0;
        break;
    case SIGSTOP:
        printf("...received SIGSTOP...\n");
        break;
    case SIGTSTP:
        printf("...received SIGTSTP...\n");
        stop_count = 1;
        break;
    case SIGINT:
        printf("...received SIGINT...\n");
        time_to_quit = 1;
        break;
    case SIGABRT:
        printf("...received SIGABRT...\n");
        time_to_quit = 1;
        break;
    case SIGQUIT:
        printf("...received SIGQUIT...\n");
        time_to_quit = 1;
        break;
    case SIGKILL:
        printf("...received SIGKILL...\n");
        time_to_quit = 1;
        break;
    default:
        printf("...received signal with ID : %d\n", signum);
        time_to_quit = 1;
        break;
    }

}

int main(int argc, char *argv[])
{
    int loop_count;

    if (argc > 1)
    {
        printf("This program needs NO arguments!\n");
        return 0;
    }
    else
    {
        printf("This program path and name is :\n%s\n", argv[0]);
        printf("The program ID is : %d\n\n", (int) getpid());
    }

    time_to_quit = 0;

    if (signal(SIGUSR1, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGUSR1\n");
    if (signal(SIGUSR2, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGUSR2\n");

//    if (signal(SIGSTOP, sig_handler) == SIG_ERR)
//        printf("\ncan't catch SIGSTOP\n");

    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");

    if (signal(SIGTSTP, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGTSTP\n");

//    if (signal(SIGKILL, sig_handler) == SIG_ERR)
//      printf("\ncan't catch SIGKILL\n");

    if (signal(SIGQUIT, sig_handler) == SIG_ERR)
      printf("\ncan't catch SIGQUIT\n");

    if (signal(SIGHUP, sig_handler) == SIG_ERR)
      printf("\ncan't catch SIGHUP\n");

    loop_count = 0;
    stop_count = 0;
    while(time_to_quit == 0)
    {
        if (stop_count == 0)
        {
            printf("program loop %d\n", loop_count);
            loop_count++;
        }
        else
            printf("stopped counting...\n");
        sleep(1);
    }

    return 0;
}

