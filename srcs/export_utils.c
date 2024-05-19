/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:22:28 by aether            #+#    #+#             */
/*   Updated: 2024/05/19 22:37:04 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_twod(char **tab, char *str)
{
	int	j;
	int	i;
	int	n;

	if (is_equal(str) == 1)
	{
		j = 0;
		while (str[j] != '=')
			j++;
		n = j;
	}
	else
		n = ft_strlen(str);
	i = 0;
	while (tab[i] != NULL)
	{
		if (ft_strncmp(tab[i], str, n) == 0)
			return (1);
		i++;
	}
	return (0);
}

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

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			return (1);
		i++;
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

/*****draft  *************/

// if (args[i][0] == '=' || ft_isdigit(args[i][0]) == 1)

// int	is_valid(char **args)
// {
// 	int	i;

// 	if (args && args[0])
// 	{
// 		i = 1;
// 		while (args[i] != NULL)
// 		{
// 			if (is_valid_start(args[i]) == 0)
// 				return (exp_str_err(args[i], "': not a valid identifier\n"), 0);
// 			if (is_valid_name(args[i]) == 0)
// 				return (exp_str_err(args[i], "': not a valid identifier\n"), 0);
// 			i++;
// 		}
// 	}
// 	return (1);
// }

// char	*dequote(char *str)
// {
// 	char	*res;
// 	int		j;
// 	int		i;

// 	j = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if ((str[i] != 34) && (str[i] != 39))
// 			j++;
// 		i++;
// 	}
// 	res = malloc(j + 1);
// 	if (res == NULL)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (str[i] != '\0')
// 	{
// 		if ((str[i] != 34) && (str[i] != 39))
// 			res[j++] = str[i];
// 		i++;
// 	}
// 	res[j] = '\0';
// 	return (res);
// }
