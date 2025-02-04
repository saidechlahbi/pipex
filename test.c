#include "libft/libft.h"
#include "pipex.h"
#include <time.h>
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
// char *
char **ft_get_all_the_paths(char **envp)
{
    char *path;
    char **paths;

    while (ft_strncmp(*envp, "PATH=", 5) != 0)
        envp++;
    path = ft_strtrim(*envp, "PATH=");
    if (!path)
        return NULL;
    paths = ft_split(path, ':');
    if (!paths)
        return NULL;
    return (paths);
}
char *ft_get_cmd_with_path(char **argument, char **envp)
{
    char **paths;
    char *cmd;
    char *ss;

    paths = ft_get_all_the_paths(envp);
    if (!paths)
        return NULL;
    while (*paths)
    {
        ss = ft_strjoin(*paths, "/");
        cmd = ft_strjoin(ss, *argument);
        free (ss);
        if (access(cmd, X_OK) == 0)
        {
            return cmd;
        }
        else
            free(cmd);
        (*envp)++;
        paths++;
    }
    return NULL;
}

int main (int ac , char **av, char **envp)
{
    if (ac == 3 && envp[0] != NULL)
    {
        int pipefd[2];
        pid_t pid1, pid2;
        char **cmd1 = ft_split(av[1], ' ');
        char **cmd2 = ft_split(av[2], ' ');
        int i = 0;

        char *str1 = ft_get_cmd_with_path(cmd1, envp);
        // printf("%s\n",str1);

        char *str2 = ft_get_cmd_with_path(cmd2, envp);
        // printf("%s\n",str2);

        cmd1[0] = str1;
        cmd2[0] = str2;


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
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            execve(cmd1[0], cmd1, envp);
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
            execve(cmd2[0], cmd2, envp);
            perror("failur in execve2\n");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2,NULL, 0);
    }else
         perror("error counting 100 \n");
   // exit(0);
}