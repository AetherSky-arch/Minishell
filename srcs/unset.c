/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:01:31 by aether            #+#    #+#             */
/*   Updated: 2024/05/16 01:15:04 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_envvar(char *vars, char *str)
{
	int	i;

	i = 0;
	while (vars[i] != '=')
		i++;
	if (ft_strncmp(vars, str, i) == 0)
		return (1);
	return (0);
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
		if (to_copy == 1)
			copy_len++;
		j++;
	}
	copy = malloc((copy_len + 1) * sizeof(char *));
	if (copy == NULL)
	{
		ft_putstr_fd("minishell: unset: malloc error\n", 2);
		return (NULL);
	}
	return (copy);
}

int	ft_unset(char **args, t_mini *mini)
{
	int		i;
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
		i = 1;
		while (args[i] != NULL)
		{
			if (is_envvar(mini->envvars[j], args[i]) == 1)
				to_copy = 0;
			i++;
		}
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

/*****draft**** */
//
// printf("apres\n");
// i = 0;
// while (mini->envvars[i])
// {
// 	printf("%s\n", mini->envvars[i]);
// 	i++;
// }
//
// printf("avant\n");
// 	i = 0;
// 	while (mini->envvars[i])
// 	{
// 		printf("%s\n", mini->envvars[i]);
// 		i++;
// 	}
// 	printf("\n");
// printf("%d\n", ft_tabstr_len(copy));
// printf("%d\n", copy_len);