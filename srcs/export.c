/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:40:42 by aether            #+#    #+#             */
/*   Updated: 2024/05/23 21:26:16 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**append(char **tab, char *str)
{
	char	**new;
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i] != NULL)
			i++;
	}
	new = malloc((i + 2) * sizeof(char *));
	if (new == NULL)
		return (NULL);
	i = 0;
	if (tab)
	{
		while (tab[i] != NULL)
		{
			new[i] = ft_strdup(tab[i]);
			i++;
		}
	}
	new[i++] = ft_strdup(str);
	new[i] = NULL;
	double_free((void **)tab);
	return (new);
}

void	replace(char **tab, char *str)
{
	int	i;
	int	j;
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
	while (ft_strncmp(tab[i], str, n) != 0)
		i++;
	free(tab[i]);
	tab[i] = ft_strdup(str);
}

void	sort_exp(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = ft_strdup(env[j]);
				free(env[j]);
				env[j] = ft_strdup(env[i]);
				free(env[i]);
				env[i] = ft_strdup(tmp);
				free(tmp);
			}
			j++;
		}
		i++;
	}
}

// ft_printf("%s", "export ");
void	export_void(char **env)
{
	int	i;

	sort_exp(env);
	i = 0;
	while (env[i] != NULL)
	{
		if (env[i][0] != '_')
		{
			ft_printf("%s", "declare -x ");
			ft_printf("%s\n", env[i]);
		}
		i++;
	}
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
		else
		{
			if (is_in_twod(mini->envvars, args[i]) && is_equal(args[i]))
				replace(mini->envvars, args[i]);
			else if (is_in_twod(mini->envvars, args[i]) == 0)
				mini->envvars = append(mini->envvars, args[i]);
		}
		i++;
	}
	return (exitcode);
}
