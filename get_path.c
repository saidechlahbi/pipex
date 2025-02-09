/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:05:32 by sechlahb          #+#    #+#             */
/*   Updated: 2025/02/09 16:12:37 by sechlahb         ###   ########.fr       */
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
