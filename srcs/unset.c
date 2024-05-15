/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:01:31 by aether            #+#    #+#             */
/*   Updated: 2024/05/15 21:29:42 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// is_envvar(args[i], envvars)
static int	is_envvar(char *str, char **vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars[i] != NULL)
	{
		j = 0;
		// while (str[j] != '=')
		while (vars[i][j] != '=')
			j++;
		if (ft_strncmp(str, vars[i], j) == 0)
			return (1);
		i++;
	}
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
	i = 1;
	j = 0;
	while (envvars[j] != NULL)
	{
		to_copy = 1;
		while (args[i] != NULL)
		{
			if (is_envvar(args[i], envvars) == 1)
				to_copy = 0;
			i++;
		}
		if (to_copy == 1)
		{
			//printf("ici\n");
			copy_len++;
		}
			
		j++;
	}
	//printf("%d\n", copy_len);
	copy = malloc((copy_len + 1) * sizeof(char *));
	if (copy == NULL)
	{
		ft_putstr_fd("minishell: unset: malloc error\n", 2);
		return (NULL); /// exit(1); !!!
	}
	//printf("%d\n", ft_tabstr_len(copy));
	return (copy);
}

// modifie !!! attention
int	ft_unset(char **args, t_mini *mini)
{
	int		i;
	int		j;
	int		k;
	char	**copy;
	int		to_copy;

	if ((args == NULL) || (args[1] == NULL))
		return (0);
	// {
	// 	ft_putstr_fd("minishell: unset: not enough arguments\n", 2);
	// 	return (1);
	// }
	// printf("avant\n");
	// i = 0;
	// while (mini->envvars[i])
	// {
	// 	printf("%s\n", mini->envvars[i]);
	// 	i++;
	// }
	// printf("\n");
	copy = envvars_copy(mini->envvars, args);
	i = 1;
	j = 0;
	k = 0;
	while (mini->envvars[j] != NULL)
	{
		to_copy = 1;
		while (args[i] != NULL)
		{
			if (is_envvar(args[i], mini->envvars) == 1)
			{
				to_copy = 0;
				
			}
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
	mini->envvars = double_dup(copy);
	double_free((void **)copy);		
	//
	// printf("apres\n");
	// i = 0;
	// while (mini->envvars[i])
	// {
	// 	printf("%s\n", mini->envvars[i]);
	// 	i++;
	// }
	return (0);
}
