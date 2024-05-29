/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:21:39 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/29 03:54:30 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_str_err(char *path, char *err_str)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("minishell: exit: ", path);
	tmp2 = ft_strjoin(tmp1, err_str);
	ft_putstr_fd(tmp2, STD_ERR);
	free(tmp1);
	free(tmp2);
}

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (9 <= c && c <= 13)
		return (1);
	return (0);
}

int	is_exit_pipe(t_mini mini)
{
	int	i;

	i = 0;
	while (i < mini.type_len)
	{
		if (mini.type[i] == PIPE)
			return (1);
		i++;
	}
	return (0);
}

int	is_space_inside(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 1)
		{
			if (i > 0 && ft_isdigit(str[i - 1]) == 1)
			{
				while (str[i] && ft_isspace(str[i]) == 1)
					i++;
				if (str[i] && ft_isdigit(str[i]) == 1)
					return (1);
			}
		}
		if (str[i])
			i++;
	}
	return (0);
}
