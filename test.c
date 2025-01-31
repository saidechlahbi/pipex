#include "pipex.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
// int main (int ac, char **av, char **envp)
// {
//     char *str[] = {"/bin/ls", "-la", NULL};
//     execve("/bin/ls", str, envp);
//     printf ("hello world \n");
// }
char *
void trim_input(char **av, char **envp)
{
    char **cmd2 = ft_split(av[2], ' ');
    char **cmd2 = ft_split(av[3], ' ');
    
    
}

int main (int ac , char **av, char **envp)
{
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1)
    {
        perror("failur in pipe\n");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 < 0)
    {
        perror("failur in fork\n");
        exit(EXIT_FAILURE);       
    }
    if (pid1 == 0)
    {
        char *str1[] = {"/bin/ls", "-la", NULL};
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        execve(str1[0], str1, envp);
        perror("failur in execve of ls\n");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 < 0)
    {
        perror("failur in fork\n");
        exit(EXIT_FAILURE);       
    }
    if (pid2 == 0)
    {
        close (pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        char *str2[] = {"/usr/bin/grep", "30", NULL};
        execve(str2[0], str2, envp);
        perror("failur in execve2\n");
        exit(EXIT_FAILURE);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2,NULL, 0);
    return 0;
}