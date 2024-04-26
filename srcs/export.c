/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <aether@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:40:42 by aether            #+#    #+#             */
/*   Updated: 2024/04/26 16:47:34 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **append(char **tab, char *str)
{
    char  **new;
    int i;

    i = 0;
    while (tab[i] != NULL)
        i++;
    if (i == 0)
        i = 1;
    new = malloc ((i + 1) * sizeof(char *));
    if (new == NULL)
        return (NULL);
    i = 0;
    while (tab[i] != NULL)
    {
        new[i] = ft_strdup(tab[i]);
        i++;
    }
    new[i++] = str;
    new[i] = NULL;
    double_free((void **)tab);
    return (new);
}

void  export(t_mini *mini, char **args)
{
    int   i;
    char  *unquoted;

    if (is_bad_assignment(args))
        return ;
    i = 0;
    while (args[i] != NULL)
    {
        unquoted = dequote(args[i]);
        if (is_no_equal(args[i]))
        {
            i++;
            continue ;
        }
        if (is_in_twod(mini->envvars, unquoted))
            // replace old with new value
        else
            // append new value to mini->envvars
        free(unquoted);
        i++;
    }
}
