/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:23:11 by sechlahb          #+#    #+#             */
/*   Updated: 2025/02/09 22:28:07 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_fd(t_pipex *pipex)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	close(pipex->fd1);
	close(pipex->fd2);
}

void	ft_open(t_pipex *pipex)
{
	pipex->fd1 = open(pipex->av[1], O_CREAT | O_RDWR, 0777);
	if (pipex->fd1 == -1)
	{
		ft_perror("open failed1\n");
		ft_free(pipex);
		exit(1);
	}
	pipex->fd2 = open(pipex->av[4], O_CREAT | O_RDWR, 0777);
	if (pipex->fd2 == -1)
	{
		close(pipex->fd1);
		ft_perror("open failed2\n");
		ft_free(pipex);
		exit(1);
	}
	if (pipe(pipex->pipefd) == -1)
	{
		close(pipex->fd1);
		close(pipex->fd2);
		ft_perror("Pipe failed\n");
		ft_free(pipex);
		exit(1);
	}
}

void	ft_first_p(t_pipex *pipex)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
	{
		ft_close_fd(pipex);
		ft_perror("fork failed\n");
		ft_free(pipex);
		exit(1);
	}
	if (pipex->pid1 == 0)
	{
		close(pipex->pipefd[0]);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		dup2(pipex->fd1, STDIN_FILENO);
		if (execve(pipex->cmd1[0], pipex->cmd1, pipex->envp) == -1)
		{
			ft_close_fd(pipex);
			ft_free(pipex);
			ft_perror("execve failed\n");
			exit(1);
		}
	}
	close(pipex->pipefd[1]);
	close(pipex->fd1);
	waitpid(pipex->pid1, NULL, 0);
}

void	ft_second_p(t_pipex *pipex)
{
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
	{
		ft_close_fd(pipex);
		ft_perror("fork failed\n");
		ft_free(pipex);
		exit(1);
	}
	if (pipex->pid2 == 0)
	{
		close(pipex->pipefd[1]);
		dup2(pipex->pipefd[0], STDIN_FILENO);
		dup2(pipex->fd2, STDOUT_FILENO);
		if (execve(pipex->cmd2[0], pipex->cmd2, pipex->envp) == -1)
		{
			ft_close_fd(pipex);
			ft_free(pipex);
			ft_perror("execve failed\n");
			exit(1);
		}
	}
	close(pipex->fd2);
	close(pipex->pipefd[0]);
	waitpid(pipex->pid2, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5 || av[2][0] == 0 || av[3][0] == 0)
		exit(1);
	ft_init(&pipex, av, envp);
	ft_open(&pipex);
	ft_first_p(&pipex);
	ft_second_p(&pipex);
	ft_free(&pipex);
	exit(0);
}
