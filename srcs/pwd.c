/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:50:26 by aether            #+#    #+#             */
/*   Updated: 2024/05/23 21:17:57 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_mini *mini)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror_close_exit("minishell: getcwd", mini, EXIT_FAILURE);
	return (0);
}

char	*get_pwd(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	*pwd;
	int		i;

	pwd = NULL;
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		pwd = malloc(sizeof(char) * (ft_strlen(cwd) + 1));
		if (!pwd)
			return (NULL);
		i = 0;
		while (cwd[i])
		{
			pwd[i] = cwd[i];
			i++;
		}
		pwd[i] = '\0';
	}
	else
		perror_close_exit("minishell: getcwd", mini, EXIT_FAILURE);
	return (pwd);
}

void	update_pwd(t_mini *mini, char *varequal, char *pwd)
{
	char	*var;

	if (mini->token && is_as_child(*mini) == 0)
	{
		if (pwd && varequal)
		{
			var = ft_strjoin(varequal, pwd);
			if (is_in_twod(mini->envvars, var))
				replace(mini->envvars, var);
			else
				mini->envvars = append(mini->envvars, var);
			free(var);
		}
	}
}
