#include "pipex.h"
#include <fcntl.h>

void ft_init_data(char **av, char **envp, t_pipex *pipex)
{
    pipex->av = av;
    pipex->envp = envp;
}

void ft_fills_argument(t_pipex *pipex)
{
    pipex->cmd1 = ft_splite(pipex->av[2], ' ');
    pipex->cmd2 = ft_splite(pipex->av[3], ' ');
}

void ft_check_argument(t_pipex *pipex)
{
    
}

void c_commands(t_pipex *pipex)
{
    //create the pipe
    if (pipe (pipex->pipefd) == -1)
    {
        perror("error\n");
        return ;
    }
// first child
    dup2(pipex->pipefd[0], STDOUT_FILENO);
    dup2(pipex->fd1, STDIN_FILENO);
    pipex->pid1 = fork();
    if (pipex->pid1 < -1)
    {
        perror("error\n");
        return ;
    }
    if (pipex->pid1 == 0)
    {
        close (fd[0]);
        dup2(fd[1], STDIN_FILENO);

    }
// seconde child
    pipex->pid2 = fork();
    if (pipex->pid2 < -1)
    {
        perror("error\n");
        return ;
    }
    if (pipex->pid2 == 0)
    {
        close (fd[1]);
        dup2(fd[0], STDOUT_FINENO);
    }

}

int main(int ac, char **av, char **envp)
{
    t_pipex pipex;
    if (ac == 5)
    {
        pipex.fd1 = open(av[1], O_RDWR | O_CREAT);
        if (pipex.fd1 < 0)
            printf("failed when was the file are open\n");
        pipex.fd2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (pipex.fd2 < 0)
            printf("failed when was the file are open\n");
        if (av[2][0] == 0 | av[3][0] == 0)
            printf("write a valide argument please \n");
        ft_init_data(av, envp, &pipex);
        
    }
    printf("error : please retry\n");
    return (1);
}
