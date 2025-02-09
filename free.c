/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:12:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/02/09 22:27:56 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	ft_free(t_pipex *pipex)
{
	if (pipex->cmd1)
		ft_free_split(pipex->cmd1);
	if (pipex->cmd2)
		ft_free_split(pipex->cmd2);
	if (pipex->paths)
		ft_free_split(pipex->paths);
}
