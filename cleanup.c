/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:25:36 by sechlahb          #+#    #+#             */
/*   Updated: 2025/02/04 23:23:04 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_free_split(char **arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i++])
        free(arr[i]);
    free(arr);
}

void cleanup(t_pipex *pipex)
{
    if (pipex->cmd1)
        ft_free_split(pipex->cmd1);
    if (pipex->cmd2)
        ft_free_split(pipex->cmd2);
    if (pipex->cmd_with_path_1)
        free(pipex->cmd_with_path_1);
    if (pipex->cmd_with_path_2)
        free(pipex->cmd_with_path_2);
    if (pipex->paths)
        ft_free_split(pipex->paths);
}
