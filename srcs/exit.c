/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:24:36 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/11 21:56:26 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_mini *mini)
{
    int exit_code;
       
    exit_code = ft_atoi(mini->cmd_arg[1]);
    free_close_exit(mini, exit_code, 0);    
}