/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:01:31 by aether            #+#    #+#             */
/*   Updated: 2024/05/23 20:54:56 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_envvar(char *var, char *str)
{
	size_t	i;
	size_t	n;

	if (is_equal(var) == 1)
	{
		i = 0;
		while (var[i] != '=')
			i++;
		n = i;
	}
	else
		n = ft_strlen(var);
	if (ft_strlen(str) == n)
	{
		if (ft_strncmp(str, var, ft_strlen(str)) == 0)
			return (1);
	}
	return (0);
}

static void	copy_len_check(int to_copy, int *copy_len)
{
	if (to_copy == 1)
		*copy_len = *copy_len + 1;
}

static char	**envvars_copy(char **envvars, char **args)
{
	int		i;
	int		j;
	int		to_copy;
	int		copy_len;
	char	**copy;

	copy_len = 0;
	j = 0;
	while (envvars[j] != NULL)
	{
		to_copy = 1;
		i = 1;
		while (args[i] != NULL)
		{
			if (is_envvar(envvars[j], args[i]) == 1)
				to_copy = 0;
			i++;
		}
		copy_len_check(to_copy, &copy_len);
		j++;
	}
	copy = malloc((copy_len + 1) * sizeof(char *));
	if (copy == NULL)
		return (ft_putstr_fd("minishell: unset: malloc error\n", 2), NULL);
	return (copy);
}

static void	check_to_copy(char **args, t_mini *mini, int *to_copy, int j)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if (is_envvar(mini->envvars[j], args[i]) == 1)
			*to_copy = 0;
		i++;
	}
}

int	ft_unset(char **args, t_mini *mini)
{
	int		j;
	int		k;
	char	**copy;
	int		to_copy;

	if ((args == NULL) || (args[1] == NULL))
		return (0);
	copy = envvars_copy(mini->envvars, args);
	j = 0;
	k = 0;
	while (mini->envvars[j] != NULL)
	{
		to_copy = 1;
		check_to_copy(args, mini, &to_copy, j);
		if (to_copy == 1)
		{
			copy[k] = ft_strdup(mini->envvars[j]);
			k++;
		}
		j++;
	}
	copy[k] = NULL;
	double_free((void **)mini->envvars);
	mini->envvars = copy;
	return (0);
}
