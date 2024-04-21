/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_to_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:00:10 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/21 20:02:05 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nbr_heredoc(t_mini mini)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < mini.type_len)
	{
		if (mini.type[i] == HEREDOC)
			count++;
		i++;
	}
	return (count);
}

// we need to be sure there is a LIMITER just after HEREDOC (to be checked in STX_ERR)
void	get_heredoc(t_mini *mini, int start)
{
	int	i;

	i = start;
	mini->is_heredoc = 0;
	if (mini->hd_fd > 0)
		close(mini->hd_fd);
	while ((i < mini->type_len) && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == HEREDOC)
		{
			mini->is_heredoc = 1;
			mini->hd_pos = i;
			mini->hd_idx = get_heredoc_idx(mini, i);
			if (mini->hd_name[mini->hd_idx])
				mini->hd_fd = open(mini->hd_name[mini->hd_idx], O_RDONLY);
		}
		i++;
	}
}

// no need if child order is well the executed order - just to be sure
int	get_heredoc_idx(t_mini *mini, int hd_pos)
{
	int	i;

	i = 0;
	mini->hd_idx = -1;
	while (i <= hd_pos)
	{
		if (mini->type[i] == HEREDOC)
			mini->hd_idx++;
		i++;
	}
	return (mini->hd_idx);
}

void	unlink_free_hdname(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->hd_name)
	{
		while (mini->hd_name[i])
		{
			unlink(mini->hd_name[i]);
			free(mini->hd_name[i]);
			i++;
		}
		free(mini->hd_name);
	}
}
