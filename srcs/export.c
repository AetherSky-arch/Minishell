/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <aether@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:40:42 by aether            #+#    #+#             */
/*   Updated: 2024/04/30 16:14:37 by aether           ###   ########.fr       */
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
	if (i == 0)
		i = 1;
	new = malloc((i + 1) * sizeof(char *));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i++] = str;
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
	tab[j] = str;
}

char	*ft_getenv(t_mini *mini, char *varname)
{
	int	i;
	int	j;

	i = 0;
	while (mini->envvars[i] != NULL)
	{
		j = 0;
		while (mini->envvars[i][j] != '=')
			j++;
		if (ft_strncmp(varname, mini->envvars[i], j) == 0)
			return (ft_substr(mini->envvars[i], j + 1,
					ft_strlen(mini->envvars[i])));
		i++;
	}
	return (ft_strdup(""));
}

void  export_void(char **env)
{
    int i;

    i = 0;
    while (env[i] != NULL)
    {
        ft_printf("%s", "declare -x ");
        ft_printf("%s\n", env[i]);
        i++;
    }
}

void	export(t_mini *mini, char **args)
{
	int		i;
	char	*unquoted;

    if ((args == NULL) || (args[0] == NULL))
    {
        export_void(mini->envvars);
    }
	if (is_bad_assignment(args))
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		unquoted = dequote(args[i]);
		if (is_no_equal(unquoted))
		{
			i++;
			free(unquoted);
			continue ;
		}
		if (is_in_twod(mini->envvars, unquoted))
			replace(mini->envvars, unquoted);
		else
			mini->envvars = append(mini->envvars, unquoted);
		i++;
	}
}
