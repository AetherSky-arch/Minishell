/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:43:09 by aether            #+#    #+#             */
/*   Updated: 2024/05/21 16:09:39 by ae7th            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int is_in(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

char  *add_envvars(t_mini *mini, char *str)
{
    t_trash trash;
    char  *res;
    char  *tmp;
    char  *tmp2;

    trash.i = 0;
    trash.formats = count_formats(str, NULL);
    trash.splitted = ft_split(str, '$');
    res = ft_strdup("");
    while (trash.formats[trash.i] != '\0')
    {
        tmp = res;
        tmp2 = find_next_element(str, &trash, mini);
        res = ft_strjoin(res, tmp2);
        free(tmp2);
        free(tmp);
    }
    double_free((void **)trash.splitted);
    free(trash.formats);
    return (res);
}

char    *envvars_unquoter(char *str)
{
    char  *res;
    int   i;

    if (str[0] == 39)
        return (NULL);
    if ((str[0] != 34) || (ft_strlen(str) < 2))
        return (ft_strdup(str));
    res = malloc(ft_strlen(str) - 1);
    if (res == NULL)
        return (NULL);
    i = 1;
    while (str[i] != 34)
    {
        res[i - 1] = str[i];
        i++;
    }
    res[i - 1] = '\0';
    return (res);
}

char  **rm_from_tokens(char **tokens, int i)
{
    int j;

    j = i;
    free(tokens[j]);
    while (tokens[j + 1] != NULL)
    {
        tokens[j] = tokens[j + 1];
        j++;
    }
    tokens[j] = NULL;
    return (tokens);
}

void    envvars_manager(char **tokens, t_mini *mini)
{
    int   i;
    char  *tmp;
    char  *tmp2;

    i = 0;
    while (tokens[i] != NULL)
    {
        tmp = envvars_unquoter(tokens[i]);
        if (tmp != NULL)
        {
            if (ft_strcmp(tmp, "$") != 0)
            {
                if (is_in(tmp, '$'))
                {
                    tmp2 = add_envvars(mini, tmp);
                    if (ft_strcmp(tmp2, "") == 0)
                        tokens = rm_from_tokens(tokens, i);
                    else
                        tokens[i] = tmp2;
                }
            }
            free(tmp);
        }
        i++;
    }
}
