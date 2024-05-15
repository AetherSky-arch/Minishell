/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:43:09 by aether            #+#    #+#             */
/*   Updated: 2024/05/15 15:43:15 by ae7th            ###   ########.fr       */
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

void    envvars_manager(char **tokens, t_mini *mini)
{
    int   i;

    i = 0;
    while (tokens[i] != NULL)
    {
        if (is_in(tokens[i], '$'))
            tokens[i] = add_envvars(mini, tokens[i]);
        i++;
    }
}
