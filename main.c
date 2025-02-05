/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:29:21 by sechlahb          #+#    #+#             */
/*   Updated: 2025/02/04 15:29:21 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void ft_pipe (t_pipex *pipex)
{
    free(pipex->cmd1[0]);
    free(pipex->cmd2[0]);
    pipex->cmd1[0] = pipex->cmd_with_path_1;
    pipex->cmd2[0] = pipex->cmd_with_path_2;

    pipex->fd1 = open (av[1], O_RDONLY);
    if (pipex->fd1 == -1)
    {
        error("error ")
    }
    if (pipe(pipex->pipefd) == -1)
    {
        error("failur in pipe\n");
        exit(EXIT_FAILURE);
    }

    pipex->pid1 = fork();
    if (pipex->pid1 < 0)
    {
        error("failur in fork\n");
        exit(EXIT_FAILURE);      
    }
    if (pipex->pid1 == 0)
    {
        close(pipex->pipefd[0]);
        dup2(pipex->pipefd[1], STDOUT_FILENO);
        execve( pipex->cmd1[0],  pipex->cmd1,  pipex->envp);
        error("failur in execve of ls\n");
        exit(EXIT_FAILURE);
    }

    pipex->pid2 = fork();
    if (pipex->pid2 < 0)
    {
        error("failur in fork\n");
        exit(EXIT_FAILURE);       
    }
    if (pipex->pid2 == 0)
    {
        close (pipex->pipefd[1]);
        dup2(pipex->pipefd[0], STDIN_FILENO);
        execve(pipex->cmd2[0], pipex->cmd2, pipex->envp);
        error("failur in execve2\n");
        exit(EXIT_FAILURE);
    }
    close(pipex->pipefd[0]);
    close(pipex->pipefd[1]);
    waitpid(pipex->pid1, NULL, 0);
    waitpid(pipex->pid2,NULL, 0);
}


int main(int ac, char **av, char **envp)
{
    t_pipex pipex;
    if (ac == 5 && envp[0] != NULL)
    {
        pipex.av = av;
        pipex.envp = envp;
        pipex.cmd1 = ft_split(av[2], ' ');
        if (!pipex.cmd1)
            return 0;
        pipex.cmd2 = ft_split(av[3], ' ');
        if (!pipex.cmd2)
            return 0; 
        pipex.cmd_with_path_1 = ft_get_cmd_with_path(&pipex, pipex.cmd1[0]);
        if (!pipex.cmd_with_path_1)
            return (0);
        pipex.cmd_with_path_2 = ft_get_cmd_with_path(&pipex, pipex.cmd2[0]);
        if (!pipex.cmd_with_path_2)
            return 0;
        ft_pipe(&pipex);
        cleanup(&pipex);
    }else
        printf("error : please retry\n");

    return (0);
}
