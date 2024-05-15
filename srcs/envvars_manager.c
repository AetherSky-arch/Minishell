/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:43:09 by aether            #+#    #+#             */
/*   Updated: 2024/05/15 20:29:26 by ae7th            ###   ########.fr       */
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
    res[i] = '\0';
    return (res);
}

void    envvars_manager(char **tokens, t_mini *mini)
{
    int   i;
    char  *tmp;

    i = 0;
    while (tokens[i] != NULL)
    {
        tmp = envvars_unquoter(tokens[i]);
        if (tmp != NULL)
        {
            if (is_in(tmp, '$'))
                tokens[i] = add_envvars(mini, tmp);
            free(tmp);
        }
        i++;
    }
}
