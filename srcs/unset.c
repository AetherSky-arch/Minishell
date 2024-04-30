/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:01:31 by aether            #+#    #+#             */
/*   Updated: 2024/04/30 18:27:21 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int  is_envvar(char *str, char **vars)
{
    int i;
    int j;

    i = 0;
    while (vars[i] != NULL)
    {
        j = 0;
        while (str[j] != '=')
            j++;
        if (ft_strncmp(str, vars[i], j) == 0)
            return (1);
        i++;
    }
    return (0);
}

static char **envvars_copier(char **envvars, char **args)
{
    int i;
    int copy_len;
    char  **copy;

    i = 0;
    copy_len = 0;
    while (args[i] != NULL)
    {
        if (is_envvar(args[i], envvars) == 0)
            copy_len++;
        i++;
    }
    copy = malloc ((copy_len + 1) * sizeof(char *));
    if (copy == NULL)
    {
        ft_putstr_fd("unset: malloc error\n", 2);
        exit(1);
    }
    return (copy);
}

int unset(char **args, t_mini *mini)
{
    int   i;
    int   j;
    char  **copy;

    if ((args == NULL) || (args[0] == NULL))
    {
        ft_putstr_fd("unset: not enough arguments\n", 2);
        return (1);
    }
    copy = envvars_copier(mini->envvars, args);
    i = 0;
    j = 0;
    while (mini->envvars[i] != NULL)
    {
        if (is_envvar(args[i], mini->envvars) == 0)
        {
            copy[j] = ft_strdup(args[i]);
            j++;
        }
        i++;
    }
    copy[j] = NULL;
    double_free((void **)mini->envvars);
    mini->envvars = copy;
    return (0);
}
