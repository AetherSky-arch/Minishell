/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:42:29 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/18 00:44:14 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_paths(t_mini *mini, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	if (envp)
	{
		while (envp[i] && (check_in_str(envp[i], "PATH=") == 0))
			i++;
		path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
		if (!path)
		{
			putstr_error((*mini).cmd_arg[0], ERR_CMD);
			free_close_exit(mini, EXIT_NOCMD, 0);
		}
		(*mini).paths = ft_split(path, ':');
		free(path);
		if (!(*mini).paths)
		{
			//double_free((void **)(*mini).paths);
			ft_putstr_fd(ERR_MAL, STD_ERR);
			free_close_exit(mini, EXIT_FAILURE, 1);
		}
		slash_paths(mini);
	}
	else
		free_close_exit(mini, EXIT_FAILURE, 0);		
}
		
		


// Only the last paths[i] is NULL
void	slash_paths(t_mini *mini)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*mini).paths[i])
	{
		tmp = ft_strdup((*mini).paths[i]);
		free((*mini).paths[i]);
		(*mini).paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
		if (!(*mini).paths[i])
		{
			//double_free((void **)(*mini).paths);			
			ft_putstr_fd(ERR_MAL, STD_ERR);
			free_close_exit(mini, EXIT_FAILURE, 1);
		}
		i++;
	}
}

// check if s2 is inside s1 from start
int	check_in_str(char *s1, char *s2)
{
	int	i;
	int	n;

	if (!s1 || !s2)
		return (0);
	i = 0;
	n = ft_strlen(s2);
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
	}
	if (i == n)
		return (1);
	return (0);
}

// Only the last paths[i] is NULL
char	*check_path(char **paths, char **cmd)
{
	int		i;
	char	*tmp;

	if (!paths || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		if (cmd[0] == NULL)
			return (NULL);
		tmp = ft_strjoin(paths[i], cmd[0]);
		if (!tmp)
			return (NULL);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}
