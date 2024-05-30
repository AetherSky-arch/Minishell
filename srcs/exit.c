/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:24:36 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/31 00:24:20 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_mini *mini, int tmp_fd)
{
	long long	exit_code;

	ft_putstr_fd("exit\n", tmp_fd);
	if (mini->cmd_arg[1])
	{
		if (check_numeric(mini->cmd_arg[1], &exit_code) == 0)
		{
			exit_str_err(mini->cmd_arg[1], ": numeric argument required\n");
			exit_code = 2;
		}
		else if (mini->cmd_arg[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", STD_ERR);
			exit_code = 1;
		}
	}
	else
		exit_code = mini->lastcode;
	if (is_in_pipe(*mini) == 0 && exit_code != 1)
	{
		close(tmp_fd);
		rl_clear_history();
		free_close_exit(mini, exit_code % 256, 0);
	}
	return (exit_code % 256);
}

int	check_numeric(char *str, long long *exit_code)
{
	int	i;
	int	k;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && ft_isspace(str[i]) == 1)
		i++;
	if (ft_isdigit(str[i]) == 0 && str[i] != '+' && str[i] != '-')
		return (0);
	if ((str[i] == '+' || str[i] == '-') && !str[i + 1])
		return (0);
	k = i;
	i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && ft_isspace(str[i]) == 0)
			return (0);
		i++;
	}
	if (is_space_inside(str) == 1)
		return (0);
	return (is_longlong(str + k, exit_code));
}

int	is_longlong_plus(char *str, long long *nbr, int i)
{
	i++;
	while (str[i])
	{
		if (*nbr > (LLONG_MAX - (str[i] - 48)) / 10)
			return (0);
		else
			*nbr = *nbr * 10 + (str[i] - 48);
		i++;
	}
	return (1);
}

int	is_longlong_minus(char *str, long long *nbr, int i)
{
	i++;
	while (str[i])
	{
		if (-*nbr < (LLONG_MIN + (str[i] - 48)) / 10)
			return (0);
		else
			*nbr = *nbr * 10 + (str[i] - 48);
		i++;
	}
	*nbr = -*nbr;
	return (1);
}

int	is_longlong(char *str, long long *nbr)
{
	int	i;

	i = 0;
	*nbr = 0;
	if (ft_strcmp("-9223372036854775808", str) == 0)
		*nbr = LLONG_MIN;
	else if (str[i] == '+')
		return (is_longlong_plus(str, nbr, i));
	else if (str[i] == '-')
		return (is_longlong_minus(str, nbr, i));
	else
	{
		while (str[i] && ft_isspace(str[i]) == 0)
		{
			if (*nbr > (LLONG_MAX - (str[i] - 48)) / 10)
				return (0);
			else
				*nbr = *nbr * 10 + (str[i] - 48);
			i++;
		}
	}
	return (1);
}
