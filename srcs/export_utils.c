/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:22:28 by aether            #+#    #+#             */
/*   Updated: 2024/05/08 00:51:12 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_in_twod(char **tab, char *str)
{
    int j;
    int i;

    j = 0;
    while (str[j] != '=')
        j++;
    i = 0;
    while (tab[i] != NULL)
    {
        if (ft_strncmp(tab[i], str, j) == 0)
            return (1);
        i++;
    }
    return (0);
}

char  *dequote(char *str)
{
    char  *res;
    int   j;
    int   i;

    j = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if ((str[i] != 34) && (str[i] != 39))
            j++;
        i++;
    }
    res = malloc (j + 1);
    if (res == NULL)
        return (NULL);
    i = 0;
    j = 0;
    while (str[i] != '\0')
    {
        if ((str[i] != 34) && (str[i] != 39))
            res[j++] = str[i];
        i++;
    }
    res[j] = '\0';
    return (res);
}

int  is_bad_assignment(char **args)
{
    int i;

    i = 1; //modif here
    while (args[i] != NULL)
    {
        if (args[i][0] == '=')
            return (ft_putstr_fd("minishell: export: bad assignment\n", 2), 1);
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
