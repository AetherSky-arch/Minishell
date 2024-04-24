/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:22:28 by aether            #+#    #+#             */
/*   Updated: 2024/04/24 17:16:07 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char  *dequote(char *str)
{
    char  *res;
    int   len;
    int   i;

    len = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if ((str[i] != 34) && (str[i] != 39))
            len++;
        i++;
    }
    res = malloc (len + 1);
    if (res == NULL)
        return (NULL);
    i = 0;
    len = 0;
    while (str[i] != '\0')
    {
        if ((str[i] != 34) && (str[i] != 39))
            res[len++] = str[i];
        i++;
    }
    res[len] = '\0';
    return (res);
}

int  is_bad_assignment(char **args)
{
    int i;

    i = 0;
    while (args[i] != NULL)
    {
        if (args[i][0] == '=')
            return (ft_putstr_fd("export: bad assignment\n", 2), 1);
        i++;
    }
    return (0);
}

int  is_no_equal(char *arg)
{
    int i;

    i = 0;
    while (arg[i] != '\0')
    {
        if (arg[i] == '=')
            return (0);
        i++;
    }
    return (1);
}
