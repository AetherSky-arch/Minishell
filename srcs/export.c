/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:40:42 by aether            #+#    #+#             */
/*   Updated: 2024/05/18 00:14:08 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**append(char **tab, char *str)
{
	char	**new;
	int		i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	// if (i == 0)
	// 	i = 1;
	new = malloc((i + 2) * sizeof(char *));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i++] = ft_strdup(str);
	new[i] = NULL;
	double_free((void **)tab);
	return (new);
}

static void	replace(char **tab, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '=')
		i++;
	j = 0;
	while (ft_strncmp(tab[j], str, i) != 0)
		j++;
	free(tab[j]);
	tab[j] = ft_strdup(str);
}

void	export_void(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_printf("%s", "declare -x ");
		ft_printf("%s\n", env[i]);
		i++;
	}
}

int	is_as_child(t_mini mini)
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

int	ft_export_to_envvars(t_mini *mini, char **args)
{
	int	i;
	int	exitcode;

	exitcode = 0;
	if (args == NULL || args[0] == NULL)
		return (1);
	if (args[1] == NULL)
		return (export_void(mini->envvars), 0);
	i = 1;
	while (args[i] != NULL)
	{
		if (is_valid(args[i]) == 0)
			exitcode = 1;
		else if (is_as_child(*mini) == 1)
			exitcode = 0;
		else if (is_equal(args[i]) == 1)
		{
			if (is_in_twod(mini->envvars, args[i]))
				replace(mini->envvars, args[i]);
			else
				mini->envvars = append(mini->envvars, args[i]);
		}
		i++;
	}
	return (exitcode);
}
