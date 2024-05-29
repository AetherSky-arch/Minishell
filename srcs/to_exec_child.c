/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:57:09 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/29 18:05:41 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_infile(t_mini *mini, int start)
{
	close(mini->fd[0]);
	check_files(mini, start);
	if (is_infile(mini, start) == 1)
	{
		if (dup2(mini->fd_in, STD_IN) == -1)
			perror_close_exit("minishell: dup2", mini, EXIT_FAILURE);
		close(mini->fd_in);
	}
	else if (mini->is_heredoc == 1)
	{
		if (dup2(mini->hd_fd, STD_IN) == -1)
			perror_close_exit("minishell: dup2", mini, EXIT_FAILURE);
		close(mini->hd_fd);
	}
	else if (mini->prev_fd0 > 0)
	{
		if (dup2(mini->prev_fd0, STD_IN) == -1)
			perror_close_exit("minishell: dup2", mini, EXIT_FAILURE);
	}
	if (mini->prev_fd0 > 0)
		close(mini->prev_fd0);
}

static void	child_outfile(t_mini *mini, int start)
{
	if (is_outfile(mini, start) == 1)
	{
		if (mini->fd_out > 0 && dup2(mini->fd_out, STD_OUT) == -1)
			perror_close_exit("minishell: dup2", mini, EXIT_FAILURE);
		close(mini->fd_out);
	}
	else if (mini->is_pipe == 1)
	{
		if (dup2(mini->fd[1], STD_OUT) == -1)
			perror_close_exit("minishell: dup2", mini, EXIT_FAILURE);
	}
	close(mini->fd[1]);
}

void	child(t_mini *mini, char **envp, int start)
{
	pid_t	pid;

	get_heredoc(mini, start);
	signal(SIGINT, &handle_sigint_in_child);
	signal(SIGQUIT, &handle_sigquit_in_child);
	pid = fork();
	if (mini->is_last_pid == 1)
		mini->last_pid = pid;
	if (pid == -1)
		perror_close_exit("minishell: fork", mini, EXIT_FAILURE);
	if (pid == 0)
	{
		child_infile(mini, start);
		child_outfile(mini, start);
		exec_arg(*mini, envp, start);
	}
	close(mini->fd[1]);
	if (mini->prev_fd0 > 0)
		close(mini->prev_fd0);
	mini->prev_fd0 = dup(mini->fd[0]);
	if (mini->prev_fd0 == -1)
		perror_close_exit("minishell: dup", mini, EXIT_FAILURE);
	close(mini->fd[0]);
}

void	close_prev_pipe(t_mini mini)
{
	if (mini.prev_fd0 > 0)
		close(mini.prev_fd0);
	if (mini.hd_fd > 0)
		close(mini.hd_fd);
}
