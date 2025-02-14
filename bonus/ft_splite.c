/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:20:42 by sechlahb          #+#    #+#             */
/*   Updated: 2025/02/14 00:37:26 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int ft_check(char *str)
// {
// 	while (*str && *str != '\'')
// 		str++;
// 	if (*str)
// 		return 1;
// 	return 0;
// }

int count_word_for_cotation(char *str)
{
    int count = 0;
    
    while (*str)
    {
        while (*str && *str == ' ')
            str++;
        if (!*str)
            break;
        if (*str == '\'')
        {
            str++;
            while (*str && *str != '\'')
                str++;
            if (*str)
                str++;
            count++;
        }
        else
        {
            while (*str && *str != ' ' && *str != '\'')
                str++;
            count++;
        }
    }
    return count;
}

char *malloc_word(const char *s, char c)
{
    int len = 0;
    while (s[len] && s[len] != c && s[len] != '\'')
        len++;
    char *word = malloc(len + 1);
    if (!word)
        return NULL;
    int i = 0;
    while (i < len)
    {
        word[i] = s[i];
        i++;
    }
    word[i] = '\0';
    return word;
}

char **ft_splite(char const *s, char c)
{
    char **strings;
    int len;
    int i;

    if (!s)
        return NULL;
    len = count_word_for_cotation((char *)s);
    strings = malloc(sizeof(char *) * (len + 1));
    if (!strings)
        return NULL;
    i = 0;
    while (*s)
    {
        while (*s && *s == c)
            s++;
        if (*s == '\'')
        {
            s++;
            const char *start = s;
            while (*s && *s != '\'')
                s++;
            int word_len = s - start;
            strings[i] = malloc(word_len + 1);
            if (!strings[i])
            {
                while (i > 0)
                    free(strings[--i]);
                free(strings);
                return NULL;
            }
            ft_strlcpy(strings[i], start, word_len + 1);
            i++;
            if (*s)
                s++;
        }
        else if (*s)
        {
            strings[i] = malloc_word(s, c);
            if (!strings[i])
            {
                while (i > 0)
                    free(strings[--i]);
                free(strings);
                return NULL;
            }
            i++;
            while (*s && *s != c && *s != '\'')
                s++;
        }
    }
    strings[i] = NULL;
    return strings;
    return NULL;
}
