/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:15:35 by aether            #+#    #+#             */
/*   Updated: 2024/05/22 23:06:38 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_dash_start(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '-')
		return (1);
	return (0);
}

static void	env_str_err(char *path, char *err_str)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("minishell: env: ", path);
	tmp2 = ft_strjoin(tmp1, err_str);
	ft_putstr_fd(tmp2, STD_ERR);
	free(tmp1);
	free(tmp2);
}

int	ft_env(t_mini *mini, char **args)
{
	int	i;

	if (args == NULL)
		return (0);
	if (args[1] != NULL)
	{
		if (is_dash_start(args[1]) == 1)
			return (ft_putstr_fd("minishell: env: invalid option\n", 2),
				EXIT_OPT);
		return (env_str_err(args[1], ERR_DIR), EXIT_NODIR);
	}
	i = 0;
	while (mini->envvars[i] != NULL)
	{
		if (is_equal(mini->envvars[i]) == 1)
			ft_printf("%s\n", mini->envvars[i]);
		i++;
	}
	return (0);
}

static int	get_last_arg(t_mini *mini)
{
	int	k;
	int	i;

	i = 0;
	k = -1;
	while (mini->token[i])
	{
		if (mini->type[i] == PIPE)
			return (-1);
		if ((mini->type[i] == ARG) || (mini->type[i] == CMD))
			k = i;
		i++;
	}
	return (k);
}

// !mini->envvars is managed by twod and append
void	update_env(t_mini *mini)
{
	int		k;
	char	*last;
	char	*tmp;

	if (mini->token)
	{
		k = get_last_arg(mini);
		if (k >= 0)
		{
			tmp = ft_strdup(mini->token[k]);
			last = ft_strjoin("_=", tmp);
			free(tmp);
			if (is_in_twod(mini->envvars, last))
				replace(mini->envvars, last);
			else
				mini->envvars = append(mini->envvars, last);
			free(last);
		}
	}
}
