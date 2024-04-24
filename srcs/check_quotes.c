/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:49:18 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/24 00:24:38 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// 34 = " / 39 = '
int	check_quotes(t_mini *mini)
{
	int	i;
	int	d_open;
	int	s_open;
	char *str;

	str = mini->fprompt;
	d_open = 0;
	s_open = 0;
	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == 39 && d_open == 0 && s_open == 0)
			s_open = 1;
		else if (str[i] == 39 && d_open == 0 && s_open == 1)
			s_open = 0;
		else if (str[i] == 34 && s_open == 0 && d_open == 0)
			d_open = 1;
		else if (str[i] == 34 && s_open == 0 && d_open == 1)
			d_open = 0;
		i++;
	}	
	return (check_quotes_output(s_open, d_open, mini));
}

int	check_quotes_output(int s_open, int d_open, t_mini *mini)
{
	if (s_open == 1)
	{
		ft_putstr_fd(ERR_SQX, STD_ERR);
		mini->stx_err_idx = 1;
		mini->exitcode = EXIT_STX;
		return (EXIT_STX);
	}
	if (d_open == 1)
	{
		ft_putstr_fd(ERR_DQX, STD_ERR);
		mini->stx_err_idx = 1;
		mini->exitcode = EXIT_STX;
		return (EXIT_STX);
	}
	return (0);
}
