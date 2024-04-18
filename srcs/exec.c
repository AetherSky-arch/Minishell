/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:07:30 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/18 04:31:23 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/********************************************************/
/****************to be reviewed with the stat functions********/
/********************************************************/
int	check_slash(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	if (str[ft_strlen(str) - 1] == '/')
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
	get_cmd_arg(&mini, start);
	if (mini.cmd_arg)
	{
		if (check_slash(mini.cmd_arg[0]) == 1)
			exec_abs(mini, envp);
		else
			exec_cmd(mini, envp);
	}
	else
	{
		ft_putstr_fd(ERR_MAL, STD_ERR);
		close_exit(mini, EXIT_FAILURE);
	}
}

// Based on the fact there is ONE cmd,
//	and it is the ONLY ONE cmd in the block.
// But args can be after files !
void	get_cmd_arg(t_mini *mini, int start)
{
	int		j;
	char	*tmp1;
	char	*tmp2;

	j = start;
	while ((j < (*mini).type_len) && (*mini).type[j] != PIPE)
	{
		if ((*mini).type[j] == CMD)
		{
			tmp1 = (*mini).token[j];
			j++;
			while (j < (*mini).type_len && (*mini).type[j] != PIPE)
			{
				if ((*mini).type[j] == ARG)
				{
					tmp2 = ft_strjoin(tmp1, " ");
					free(tmp1);
					tmp1 = ft_strjoin(tmp2, (*mini).token[j]);
					free(tmp2);
				}
				j++;
			}
		}
		else
			j++;
	}
	(*mini).cmd_arg = ft_split(tmp1, ' ');
	ft_putstr_fd((*mini).cmd_arg[0], STD_ERR); /*************issue here*/
	free(tmp1);
}

// int execve(const char *pathname, char *const argv[], char *const envp[]);
void	exec_cmd(t_mini mini, char **envp)
{
	char	*path_cmd;

	get_paths(&mini, envp);
	path_cmd = check_path(mini.paths, mini.cmd_arg);
	if (!path_cmd)
	{
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
