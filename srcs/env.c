/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:15:35 by aether            #+#    #+#             */
/*   Updated: 2024/05/21 00:18:49 by caguillo         ###   ########.fr       */
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
		// return (ft_putstr_fd("minishell: env: invalid argument\n", 2),
		// 	EXIT_FAILURE);
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

// // !mini->envvars is managed by twod and append
// void	update_env(t_mini *mini)
// {
// 	int		i;
// 	char	*last;
// 	char	*tmp;

// 	if (mini->cmd_arg)
// 	{
// 		i = 0;
// 		tmp = NULL;
// 		while (mini->cmd_arg[i])
// 			i++;
// 		if (mini->cmd_arg[i])
// 			tmp = ft_strdup(mini->cmd_arg[i]);
// 		last = ft_strjoin("_=", tmp);
// 		free(tmp);
// 		if (is_in_twod(mini->envvars, last))
// 			replace(mini->envvars, last);
// 		else
// 			mini->envvars = append(mini->envvars, last);
// 		free(last);
// 	}
// }
