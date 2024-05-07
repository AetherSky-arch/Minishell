/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:15:35 by aether            #+#    #+#             */
/*   Updated: 2024/05/08 01:03:11 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_env(char **args, t_mini *mini)
{
    int i;

    if ((args != NULL) || (args[1] != NULL)) // Modif a revoir
    {
        ft_putstr_fd("minishell: env: invalid argument\n", 2);
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
