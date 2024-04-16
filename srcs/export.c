/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <aether@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:40:42 by aether            #+#    #+#             */
/*   Updated: 2024/04/16 21:42:59 by aether           ###   ########.fr       */
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

static int  in(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

static int  in_twod(char **tab, char *str)
{
    int i;

    i = 0;
    while (tab[i] != NULL)
    {
        if (ft_strcmp(str, tab[i]) == 0)
            return (i);
        i++;
    }
    return (-1);
}

void  create_env_var(t_mini *mini, char *var)
{
    char  *final;

    if (in_twod(mini->envvars, var) != -1)
    {
        final = ft_strjoin(var, "=");
        append(mini->envvars, final);
    }
    else
        append(mini->envvars, var);
}

void  export(t_mini *mini, char *var)
{
    if (var[0] == '=')
    {
        ft_putstr_fd("export: bad assignment", 2);
        return ;
    }
    if (in(var, '=') == -1)
        create_env_var(mini, var);
}
