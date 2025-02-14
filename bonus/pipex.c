/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:23:11 by sechlahb          #+#    #+#             */
/*   Updated: 2025/02/14 17:34:40 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_exit(t_pipex *pipex, char *str, int status)
{
	perror(str);
	perror("\n");
	ft_free(pipex);
	exit(status);
}

void	ft_open(t_pipex *pipex)
{
	pipex->fd1 = open(pipex->av[1], O_RDONLY, 0644);
	if (pipex->fd1 == -1)
		perror("open failed1\n");
	pipex->fd2 = open(pipex->av[pipex->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd2 == -1)
		perror("open failed2\n");
}
void ft_pipe(t_pipex *pipex, int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("Pipe failed\n");
		ft_free(pipex);
		exit(1);
	}
}

void	ft_first_p(t_pipex *pipex, int *pipefd)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		ft_exit(pipex, "fork failure", 1);
	if (pipex->pid1 == 0)
	{
        if (pipex->cmd1[0] == NULL)
        {
            ft_free(pipex);
            exit(127);
        }
        if (pipex->fd1 == -1)
        {
            ft_free(pipex);
            exit(1);  
        }
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		dup2(pipex->fd1, STDIN_FILENO);
		if (execve(pipex->cmd1[0], pipex->cmd1, pipex->envp) == -1)
			ft_exit(pipex, "fork failure", 127);
	}
	close(pipefd[1]);
	close(pipex->fd1);
}

void	ft_second_p(t_pipex *pipex, int *pipefd)
{
	pipex->pidn = fork();
	if (pipex->pidn == -1)
		ft_exit(pipex, "fork failure", 1);
	if (pipex->pidn == 0)
	{
		if (pipex->cmdn[0] == NULL)
		{
			ft_free(pipex);
			exit(127);
		}
		if (pipex->fd2 == -1)
		{
			ft_free(pipex);
			exit(1);
		}
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		dup2(pipex->fd2, STDOUT_FILENO);
		if (execve(pipex->cmdn[0], pipex->cmdn, pipex->envp) == -1)
			ft_exit(pipex, "fork failure", 127);

	}
	close(pipex->fd2);
	close(pipefd[0]);
}

void ft_middle_procces(t_pipex *pipex, int *pipefd1, int *pipefd2, int i)
{
	pid_t pid;
	char **cmd;

	cmd = last_cmd(pipex, pipex->av[i]);
	pid = fork();
	if (pid == -1)
		ft_exit(pipex, "fork failure", 1);
	if (pid == 0)
	{
		if (cmd[0] == NULL)
		{
			ft_free(pipex);
			exit(127);
		}
		//close(pipefd2[1]);
		dup2(pipefd1[0], STDIN_FILENO);
		dup2(pipefd2[1], STDOUT_FILENO);
		if (execve(cmd[0], cmd, pipex->envp) == -1)
			ft_exit(pipex, "fork failure", 127);

	}
	close(pipefd2[1]);
	close(pipefd1[0]);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int (status1), (status2), (i);
	int (*pipefd1), (*pipefd2);

	status1 = 0;
	status2 = 0;
	i = 2;
	if (ac != 5 || av[2][0] == 0 || av[3][0] == 0)
		exit(1);
	ft_init(&pipex, ac, av, envp);
	ft_open(&pipex);
	pipex.cmd1 = last_cmd(&pipex, av[2]);
	pipex.cmdn = last_cmd(&pipex, av[ac - 2]);

	pipefd1 = malloc(8);
	ft_pipe(&pipex, pipefd1);
	while (i < ac -1)
	{
		if (i == 2)
			ft_first_p(&pipex, pipefd1);
		else
		{
			pipefd2 = malloc(8);
			ft_pipe(&pipex, pipefd2);
			ft_middle_procces(&pipex, pipefd1, pipefd2, i);
			free(pipefd1);
			pipefd1 = pipefd2;
		}
		if (i == ac - 2)
			ft_second_p(&pipex, pipefd2);
		i++;
	}
	
	waitpid(pipex.pid1, &status1, WUNTRACED);
    waitpid(pipex.pidn, &status2, WUNTRACED); 
	
	ft_free(&pipex);
	exit(WEXITSTATUS(status2));
}
