/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:15:35 by aether            #+#    #+#             */
/*   Updated: 2024/04/30 17:00:42 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int env(char **args, t_mini *mini)
{
    int i;

    if ((args != NULL) || (args[0] != NULL))
    {
        ft_putstr_fd("env: invalid argument\n", 2);
        return (1);
    }
    i = 0;
    while (mini->envvars[i] != NULL)
    {
        ft_printf("%s\n", mini->envvars[i]);
        i++;
    }
    return (0);
}
