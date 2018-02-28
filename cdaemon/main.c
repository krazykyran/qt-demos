#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

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
    /* Our process ID and session ID */
    pid_t pid, sid;

    if (argc > 1)
    {
        puts("This program needs NO arguments!\n");
        return 0;
    }
    else
    {
        printf("This program path and name is :\n%s\n", argv[0]);
        printf("The program ID is : %d\n", (int) getpid());
        printf("The parent ID is  : %d\n", (int) getppid());
    }

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        puts("Exiting... unable to fork parent process!");
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then we can exit the parent process */
    if (pid > 0) {
        printf("Forked child ID is : %d\n", (int) pid);
        puts("Exiting... success.");
        exit(EXIT_SUCCESS);
    }

    /* Change the file mode mask */
    umask(0);

    /* Open any logs here */

    /* Create a new session ID for the child process */
    sid = setsid();
    if (sid < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory */
    if ((chdir("/")) < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* Daemon-specific initialization goes here */

    /* An infinite loop */
    while (1) {
        /* Do some task here */

        sleep(30); /* Child waits for 30 seconds */
    }
     /* Then exit with success */
     exit(EXIT_SUCCESS);

    time_to_quit = 0;

    if (signal(SIGUSR1, sig_handler) == SIG_ERR)
        puts("\ncan't catch SIGUSR1\n");
    if (signal(SIGUSR2, sig_handler) == SIG_ERR)
        puts("\ncan't catch SIGUSR2\n");

//    if (signal(SIGSTOP, sig_handler) == SIG_ERR)
//        printf("\ncan't catch SIGSTOP\n");

    if (signal(SIGINT, sig_handler) == SIG_ERR)
        puts("\ncan't catch SIGINT\n");

    if (signal(SIGTSTP, sig_handler) == SIG_ERR)
        puts("\ncan't catch SIGTSTP\n");

    if (signal(SIGCONT, sig_handler) == SIG_ERR)
        puts("\ncan't catch SIGCONT\n");

//    if (signal(SIGKILL, sig_handler) == SIG_ERR)
//      puts("\ncan't catch SIGKILL\n");

    if (signal(SIGQUIT, sig_handler) == SIG_ERR)
      puts("\ncan't catch SIGQUIT\n");

    if (signal(SIGHUP, sig_handler) == SIG_ERR)
      puts("\ncan't catch SIGHUP\n");

    loop_count = 0;
    stop_count = 0;
    while(time_to_quit == 0)
    {
        if (stop_count == 0)
        {
//            printf("program loop %d\n", loop_count);
            write(1,".",1);
            loop_count++;
        }
        else
//            puts("Stopped counting...");
            write(1,"z",1);
        sleep(1);
    }

    return 0;
}

