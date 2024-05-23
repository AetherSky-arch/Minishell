/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:52:56 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/24 00:10:56 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_mini mini, int start)
{
	int	i;

	i = start;
	while ((i < mini.type_len) && (mini.type[i] != PIPE))
	{
		if (mini.type[i] == CMD)
		{
			if (ft_strcmp(mini.token[i], "cd") == 0)
				return (0);
			if (ft_strcmp(mini.token[i], "echo") == 0)
				return (1);
			if (ft_strcmp(mini.token[i], "env") == 0)
				return (2);
			if (ft_strcmp(mini.token[i], "exit") == 0)
				return (3);
			if (ft_strcmp(mini.token[i], "export") == 0)
				return (4);
			if (ft_strcmp(mini.token[i], "pwd") == 0)
				return (5);
			if (ft_strcmp(mini.token[i], "unset") == 0)
				return (6);
		}
		i++;
	}
	return (-1);
}

// which_builtin
static void	wh_b(t_mini *mini, int start, int tmp_out)
{
	int	k;

	k = is_builtin(*mini, start);
	if (k == CD)
		mini->exitcode = ft_chd(mini);
	if (k == ECHO)
		mini->exitcode = ft_echo(mini->cmd_arg);
	if (k == ENV)
		mini->exitcode = ft_env(mini, mini->cmd_arg);
	if (k == EXIT)
		mini->exitcode = ft_exit(mini, tmp_out);
	if (k == EXPORT)
		mini->exitcode = ft_export_to_envvars(mini, mini->cmd_arg);
	if (k == PWD)
		mini->exitcode = ft_pwd(mini);
	if (k == UNSET)
		mini->exitcode = ft_unset(mini->cmd_arg, mini);
}

void	builtin(t_mini *mini, int start)
{
	int	tmp_out;

	tmp_out = dup(STD_OUT);
	if (tmp_out == -1)
		perror_close_exit("minishell: dup", mini, EXIT_FAILURE);
	if (builtin_files(mini, start) == SUCCESS)
	{
		create_cmd_arg(mini, start);
		if (mini->cmd_arg && mini->cmd_arg[0])
			(wh_b(mini, start, tmp_out), double_free((void **)(mini->cmd_arg)));
		else
		{
			ft_putstr_fd(ERR_MAL, STD_ERR);
			if (dup2(tmp_out, STD_OUT) == -1)
				perror_close_exit("minishell: dup2", mini, EXIT_FAILURE);
			close(tmp_out);
			free_close_exit(mini, EXIT_FAILURE, 0);
		}
	}
	else
		mini->exitcode = 1;
	if (dup2(tmp_out, STD_OUT) == -1)
		perror_close_exit("minishell: dup2", mini, EXIT_FAILURE);
	close(tmp_out);
}

// 0 on success = infile opened (and closed) // -1 on error
int	builtin_infile(t_mini *mini, int i)
{
	char	*tmp;

	if (mini->type[i] == INFILE)
	{
		if (is_ambigous(mini->token[i]))
			return (ft_putstr_fd(ERR_AMB, STD_ERR), -1);
		mini->fd_in = open(mini->token[i], O_RDONLY);
		if (mini->fd_in < 0)
		{
			tmp = ft_strjoin("minishell: ", mini->token[i]);
			perror(tmp);
			free(tmp);
			return (-1);
		}
		close(mini->fd_in);
	}
	return (0);
}

// 1 on success = outfile opened // -1 on error
int	builtin_outfile(t_mini *mini, int i)
{
	char	*tmp;

	if (is_ambigous(mini->token[i]))
		return (ft_putstr_fd(ERR_AMB, STD_ERR), -1);
	if (mini->fd_out > 0)
		close(mini->fd_out);
	if (mini->type[i] == OUTFILE)
		mini->fd_out = open(mini->token[i], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (mini->type[i] == OUTFAPP)
		mini->fd_out = open(mini->token[i], O_WRONLY | O_APPEND | O_CREAT,
				0666);
	if (mini->fd_out < 0)
	{
		tmp = ft_strjoin("minishell: ", mini->token[i]);
		perror(tmp);
		free(tmp);
		return (-1);
	}
	return (1);
}
