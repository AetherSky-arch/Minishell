/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:28:48 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/24 00:05:04 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	close_and_dup(t_mini *mini)
{
	if (mini->prev_fd0 > 0)
		close(mini->prev_fd0);
	mini->prev_fd0 = dup(mini->fd[0]);
	if (mini->prev_fd0 == -1)
		perror_close_exit("minishell: dup", mini, EXIT_FAILURE);
	close(mini->fd[0]);
}

static void	dup_if_pipe(t_mini *mini)
{
	if (dup2(mini->fd[1], STD_OUT) == -1)
		perror_close_exit("minishell: dup2", mini, EXIT_FAILURE);
}

static void	dup_if_files_ok(t_mini *mini)
{
	if (dup2(mini->fd_out, STD_OUT) == -1)
		perror_close_exit("minishell: dup2", mini, EXIT_FAILURE);
	close(mini->fd_out);
}

// res receive 0 from infile, 1 from outfile, -1 on error
int	builtin_files(t_mini *mini, int start)
{
	int	i;
	int	res;

	close_and_dup(mini);
	i = start;
	res = 0;
	while ((i < mini->type_len) && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == INFILE)
		{
			if (builtin_infile(mini, i) == -1)
				return (close(mini->fd[1]), FAILURE);
		}
		if (mini->type[i] == OUTFILE || mini->type[i] == OUTFAPP)
			res = builtin_outfile(mini, i);
		if (res == -1)
			return (close(mini->fd[1]), FAILURE);
		i++;
	}
	if (res == 1)
		dup_if_files_ok(mini);
	else if (mini->is_pipe == 1)
		dup_if_pipe(mini);
	return (close(mini->fd[1]), SUCCESS);
}
