/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:50:38 by sechlahb          #+#    #+#             */
/*   Updated: 2025/01/30 17:50:38 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char **ft_get_all_the_paths(char **envp)
{
    char *path;
    char **paths;

    while (ft_strncmp(*envp, "PATH=", 5) != 0)
        envp++;
    path = ft_strtrim(*envp, "PATH=");
    if (!path)
        return (NULL);
    paths = ft_split(path, ':');
    if (!paths)
        return (free(path), NULL);
    return (free(path), paths);
}

char *ft_get_cmd_with_path(t_pipex *pipex, char *cmd)
{
    char *str;
    int i;
    char *ss;

    pipex->paths = ft_get_all_the_paths(pipex->envp);
    if (!pipex->paths)
        return NULL;
    i = 0;
    while (pipex->paths[i])
    {
        ss = ft_strjoin(pipex->paths[i], "/");
        if (!ss)
            return (NULL);
        str = ft_strjoin(ss, cmd);
        if (!str)
            return (free(ss), NULL);
        free (ss);
        if (access(str, X_OK) == 0)
            return (str);
        else
            free(str);
        i++;
    }
    return (free(str), NULL);
}
