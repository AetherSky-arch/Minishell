/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:57:09 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/30 17:39:33 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_infile(t_mini *mini, int start)
{
	close(mini->fd[0]);
	check_files(mini, start);
	if (is_infile(mini, start) == 1)
	{
		dup2(mini->fd_in, STD_IN);
		close(mini->fd_in);
	}
	else if (mini->is_heredoc == 1)
	{
		dup2(mini->hd_fd, STD_IN);
		close(mini->hd_fd);
	}
	else if (mini->prev_fd0 > 0)
		dup2(mini->prev_fd0, STD_IN);
	if (mini->prev_fd0 > 0)
		close(mini->prev_fd0);
}

static void	child_outfile(t_mini *mini, int start, int tmp_out)
{
	if (is_outfile(mini, start) == 1)
	{
		dup2(mini->fd_out, STD_OUT);
		close(mini->fd_out);
	}
	else if (mini->is_pipe == 1)
		dup2(mini->fd[1], STD_OUT);
	else
		dup2(tmp_out, STD_OUT);
	close(tmp_out);
	close(mini->fd[1]);
}

void	child(t_mini *mini, char **envp, int start)
{
	pid_t	pid;
	int		tmp_out;

	tmp_out = dup(STD_OUT);
	if (tmp_out == -1)
		perror("minishell: dup");
	(get_heredoc(mini, start), signal(SIGINT, &handle_sigint_in_child));
	signal(SIGQUIT, &handle_sigquit_in_child);
	pid = fork();
	if (mini->is_last_pid == 1)
		mini->last_pid = pid;
	if (pid == -1)
		perror_close_exit("minishell: fork", mini, EXIT_FAILURE);
	if (pid == 0)
	{
		(close(tmp_out), child_infile(mini, start));
		(child_outfile(mini, start, tmp_out), exec_arg(*mini, envp, start));
	}
	close(mini->fd[1]);
	if (mini->prev_fd0 > 2)
		close(mini->prev_fd0);
	mini->prev_fd0 = dup(mini->fd[0]);
	if (mini->prev_fd0 == -1)
		perror("minishell: dup");
	(close(mini->fd[0]), close(tmp_out));
}

void	close_prev_pipe(t_mini mini)
{
	if (mini.prev_fd0 > 2)
		close(mini.prev_fd0);
	if (mini.hd_fd > 2)
		close(mini.hd_fd);
}
