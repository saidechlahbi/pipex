/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:19:26 by sechlahb          #+#    #+#             */
/*   Updated: 2025/02/13 15:24:13 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_all_the_paths(t_pipex *pipex)
{
	int		i;
	char	*str;
	char	**paths;

	i = 0;
	while (ft_strncmp(pipex->envp[i], "PATH=", 5) != 0)
		i++;
	str = ft_strtrim(pipex->envp[i], "PATH=");
	if (!str)
		return ;
	paths = ft_split(str, ':');
	if (!paths)
	{
		free(str);
		return ;
	}
	pipex->paths = paths;
	free(str);
}

char	*ft_right_path(t_pipex *pipex, char *comand)
{
	char	*str;
	char	*cmd;
	int		i;

	i = 0;
	if (!pipex->paths)
		return (NULL);
	if (access(comand, X_OK) == 0)
		return (ft_strdup(comand));
	while (pipex->paths[i])
	{
		str = ft_strjoin(pipex->paths[i], "/");
		if (!str)
			return (NULL);
		cmd = ft_strjoin(str, comand);
		if (!cmd)
			return (free(str), NULL);
		free(str);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

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

