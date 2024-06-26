/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:07:30 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/24 16:09:13 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_slash(char *str)
{
	size_t	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] == '/')
		{
			if (i > 0 && str[i - 1] == ' ')
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

void	exec_arg(t_mini mini, char **envp, int start)
{
	create_cmd_arg(&mini, start);
	if (mini.cmd_arg)
	{
		if (check_slash(mini.cmd_arg[0]) == 1)
		{
			is_a_directory(&mini, mini.cmd_arg[0]);
			exec_abs(mini, envp);
		}
		else
			exec_cmd(mini, envp);
	}
	else if (mini.type)
		free_close_exit(&mini, EXIT_SUCCESS, 0);
	else
	{
		ft_putstr_fd(ERR_MAL, STD_ERR);
		free_close_exit(&mini, EXIT_FAILURE, 0);
	}
}

//

// int execve(const char *pathname, char *const argv[], char *const envp[]);
void	exec_cmd(t_mini mini, char **envp)
{
	char	*path_cmd;

	if (!mini.cmd_arg || !mini.cmd_arg[0])
		free_close_exit(&mini, EXIT_SUCCESS, 0);
	get_paths(&mini, envp);
	path_cmd = check_path(mini.paths, mini.cmd_arg);
	if (!path_cmd || ft_strlen(mini.cmd_arg[0]) == 0)
	{
		if (path_cmd)
			free(path_cmd);
		putstr_error(mini.cmd_arg[0], ERR_CMD);
		free_close_exit(&mini, EXIT_NOCMD, 1);
	}
	if (execve(path_cmd, mini.cmd_arg, envp) == -1)
	{
		perror("minishell: execve");
		free(path_cmd);
		free_close_exit(&mini, EXIT_FAILURE, 1);
	}
}

void	exec_abs(t_mini mini, char **envp)
{
	if (access(mini.cmd_arg[0], X_OK) != 0)
	{
		if (access(mini.cmd_arg[0], F_OK) != 0)
		{
			putstr_error(mini.cmd_arg[0], ERR_DIR);
			free_close_exit(&mini, EXIT_NODIR, 0);
		}
		putstr_error(mini.cmd_arg[0], ERR_ACX);
		free_close_exit(&mini, EXIT_DENIED, 0);
	}
	if (execve(mini.cmd_arg[0], mini.cmd_arg, envp) == -1)
	{
		perror("minishell: execve");
		free_close_exit(&mini, EXIT_FAILURE, 0);
	}
}

// != 0 => is a directory
void	is_a_directory(t_mini *mini, char *is_cmd_or_dir)
{
	struct stat	statbuf;

	if (is_cmd_or_dir)
	{
		if (stat(is_cmd_or_dir, &statbuf) != -1)
		{
			if (S_ISDIR(statbuf.st_mode) != 0)
			{
				putstr_error(is_cmd_or_dir, ERR_ISD);
				free_close_exit(mini, EXIT_DENIED, 0);
			}
		}
		else if (errno == EACCES)
		{
			putstr_error(is_cmd_or_dir, ERR_ACX);
			free_close_exit(mini, EXIT_DENIED, 0);
		}
	}
}

// same as create_cmd_arg in buitins.c
// void	get_cmd_arg(t_mini *mini, int start)
// {
// 	int		j;
// 	char	*tmp1;
// 	char	*tmp2;

// 	j = start;
// 	tmp1 = NULL;
// 	while ((j < (*mini).type_len) && (*mini).type[j] != PIPE)
// 	{
// 		if ((*mini).type[j] == CMD)
// 		{
// 			tmp1 = ft_strdup((*mini).token[j]);
// 			j++;
// 			while (j < (*mini).type_len && (*mini).type[j] != PIPE)
// 			{
// 				if ((*mini).type[j] == ARG)
// 				{
// 					tmp2 = ft_strjoin(tmp1, " ");
// 					free(tmp1);
// 					tmp1 = ft_strjoin(tmp2, (*mini).token[j]);
// 					free(tmp2);
// 				}
// 				j++;
// 			}
// 		}
// 		else
// 			j++;
// 	}
// 	(*mini).cmd_arg = ft_split(tmp1, ' ');
// 	free(tmp1);
// }
