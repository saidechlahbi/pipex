/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:19:26 by sechlahb          #+#    #+#             */
/*   Updated: 2025/02/09 22:29:14 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init(t_pipex *pipex, char **av, char **envp)
{
	char	*a;
	char	*b;

	pipex->av = av;
	pipex->envp = envp;
	pipex->cmd1 = ft_split(av[2], ' ');
	if (!pipex->cmd1)
		exit(1);
	pipex->cmd2 = ft_split(av[3], ' ');
	if (!pipex->cmd2)
		exit(1);
	ft_all_the_paths(pipex);
	a = pipex->cmd1[0];
	b = pipex->cmd2[0];
	pipex->cmd1[0] = ft_right_path(pipex, pipex->cmd1[0]);
	pipex->cmd2[0] = ft_right_path(pipex, pipex->cmd2[0]);
	free(a);
	free(b);
}

void	ft_perror(char *str)
{
	while (*str)
		write(1, str++, 1);
}
