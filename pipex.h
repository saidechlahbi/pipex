/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:29:26 by sechlahb          #+#    #+#             */
/*   Updated: 2025/02/12 21:11:22 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
#define PIPEX_H

#include "libft/libft.h"
#include <fcntl.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
typedef struct s_pipex{
    char **av;
    char **envp;
    int pipefd[2]; 
    int fd1;
    int fd2;
    pid_t pid1;
    pid_t pid2;
    char **cmd1;
    char **cmd2;
    char **paths;
}   t_pipex;

void ft_all_the_paths(t_pipex *pipex);
void ft_free_split(char **str);
char *ft_right_path(t_pipex *pipex, char *comand);
void ft_free(t_pipex *pipex);
void ft_init(t_pipex *pipex, char **av, char **envp);

#endif