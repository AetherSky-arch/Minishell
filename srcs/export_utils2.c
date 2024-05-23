/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:22:28 by aether            #+#    #+#             */
/*   Updated: 2024/05/23 21:26:20 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid(char *str)
{
	if (str)
	{
		if (is_valid_start(str) == 0)
			return (exp_str_err(str, "': not a valid identifier\n"), 0);
		if (is_valid_name(str) == 0)
			return (exp_str_err(str, "': not a valid identifier\n"), 0);
	}
	return (1);
}

int	is_equal(char *arg)
{
	int	i;

	if (arg)
	{
		i = 0;
		while (arg[i] != '\0')
		{
			if (arg[i] == '=')
				return (1);
			i++;
		}
	}
	return (0);
}

void	exp_str_err(char *arg, char *err_str)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("minishell: export: `", arg);
	tmp2 = ft_strjoin(tmp1, err_str);
	ft_putstr_fd(tmp2, STD_ERR);
	free(tmp1);
	free(tmp2);
}

int	is_valid_start(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '_')
		return (1);
	return (ft_isalpha(str[0]));
}

int	is_valid_name(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if ((ft_isalnum(str[i]) != 1) && (str[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}
