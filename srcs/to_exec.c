/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:50:16 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/31 01:15:55 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nbr_block(t_mini mini)
{
	int	i;
	int	nbr;

	if (!(mini.type))
		return (0);
	i = 0;
	nbr = 1;
	while (i < mini.type_len)
	{
		if (mini.type[i] == PIPE)
			nbr++;
		i++;
	}
	return (nbr);
}

static void	blocks_to_exec_last_or_pipe(t_mini *mini, int j)
{
	if (j == mini->type_len)
	{
		mini->is_last_pid = 1;
		mini->is_pipe = 0;
	}
	else if (mini->type[j] == PIPE)
		mini->is_pipe = 1;
}

// j = index of the next pipe (so len-1 if no pipe)
// if no pipe (just one cmd or heredoc), same as usual case,
// the pipe is just not used and closed
void	blocks_to_exec(t_mini *mini, char **envp, int nbr_block)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	start = 0;
	j = 0;
	while (i < nbr_block)
	{
		while ((j < mini->type_len) && (mini->type[j] != PIPE))
			j++;
		blocks_to_exec_last_or_pipe(mini, j);
		if (pipe(mini->fd) == -1)
			perror_close_exit("minishell: pipe", mini, EXIT_FAILURE);
		else if (is_builtin(*mini, start) != -1)
			builtin(mini, start);
		else
			child(mini, envp, start);
		if (j < mini->type_len)
			j++;
		start = j;
		i++;
	}
}
