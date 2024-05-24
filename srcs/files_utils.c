/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:05:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/24 01:05:31 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_ambigous(char *str)
{
	if (!str)
		return (0);
	if (ft_strlen(str) == 1 && str[0] == '*')
		return (1);
	return (0);
}

void	free_ambigous(t_mini *mini, char *str)
{
	if (!str)
		return ;
	if (ft_strlen(str) == 1 && str[0] == '*')
	{
		ft_putstr_fd(ERR_AMB, STD_ERR);
		double_free((void **)mini->hd_name);
		double_free((void **)mini->token);
		double_free((void **)mini->envvars);
		free(mini->fprompt);
		free(mini->type);
		mini->exitcode = EXIT_FAILURE;
		close_exit(*mini, EXIT_FAILURE);
	}
}
