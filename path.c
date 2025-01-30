#include "libft/libft.h"
#include "pipex.h"

char *get_path(char **envp)
{
    while (*envp)
    {
        if (ft_strncmp(*envp, "PATH=", 5) == 0)
        {
            char *str = ft_strtrim(ft_strdup(*envp), "PATH=")
        }else
            (*envp)++;
    }
}