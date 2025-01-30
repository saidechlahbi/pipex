#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
typedef struct s_pipex{
    int pipefd[2];
    char **av;
    char **envp;
    pid_t pid1;
    pid_t pid2;
    int fd1;
    int fd2;
    char **cmd1;
    char **cmd2;
}   t_pipex;

char **ft_splite(char *str, char sep);
char	*ft_strjoin(char const *s1, char const *s2);

#endif