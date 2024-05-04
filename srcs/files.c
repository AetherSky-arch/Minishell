/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:07:15 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/04 20:41:44 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_infile(t_mini *mini, int start)
{
	int	i;
	int	is_infile;
	int	prev_fd_in;

	i = start;
	is_infile = 0;
	prev_fd_in = -1;
	while ((i < mini->type_len) && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == INFILE)
		{
			open_infile(mini, mini->token[i]);
			if (mini->hd_pos < i)
			{
				is_infile = 1;
				if (prev_fd_in > -1)
					close(prev_fd_in);
				prev_fd_in = mini->fd_in;
			}
			else
				close(mini->fd_in);
		}
		i++;
	}
	return (is_infile);
}

// if exist and readable --> open
// else exit (from child)
void	open_infile(t_mini *mini, char *infile)
{
	mini->fd_in = open(infile, O_RDONLY);
	if (mini->fd_in < 0)
		perror_open_free(mini, infile);
}

int	is_outfile(t_mini *mini, int start)
{
	int	i;
	int	is_outfile;

	i = start;
	is_outfile = 0;
	while ((i < mini->type_len) && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == OUTFILE || mini->type[i] == OUTFAPP)
		{
			if (mini->fd_out > 0)
				close(mini->fd_out);
			is_outfile = 1;
		}
		if (mini->type[i] == OUTFILE)
			mini->fd_out = open(mini->token[i], O_WRONLY | O_TRUNC | O_CREAT,
					0666);
		if (mini->type[i] == OUTFAPP)
			mini->fd_out = open(mini->token[i], O_WRONLY | O_APPEND | O_CREAT,
					0666);
		if (mini->fd_out < 0)
			perror_open_free(mini, mini->token[i]);
		i++;
	}
	return (is_outfile);
}
