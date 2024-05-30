/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_to_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:00:10 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/30 16:03:25 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nbr_heredoc(t_mini mini)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < mini.type_len - 1)
	{
		if (mini.type[i] == HEREDOC)
		{
			if ((mini.type[i + 1] != LIMITER) || (mini.stx_err_idx == i + 1))
				return (count);
			else
				count++;
		}
		i++;
	}
	return (count);
}

void	get_heredoc(t_mini *mini, int start)
{
	int	i;

	i = start;
	mini->is_heredoc = 0;
	if (mini->hd_fd > 2)
		close(mini->hd_fd);
	while ((i < mini->type_len) && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == HEREDOC)
		{
			if (mini->hd_fd > 2)
				close(mini->hd_fd);
			mini->is_heredoc = 1;
			mini->hd_pos = i;
			mini->hd_idx = get_heredoc_idx(mini, i);
			if (mini->hd_name[mini->hd_idx])
				mini->hd_fd = open(mini->hd_name[mini->hd_idx], O_RDONLY);
		}
		i++;
	}
}

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

int	check_heredoc(t_mini *mini)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < mini->type_len)
	{
		if (mini->type[i] == HEREDOC)
		{
			if ((i + 1 == mini->type_len) || (mini->type[i + 1] != LIMITER))
			{
				if (i + 1 == mini->type_len)
					tmp = ft_strjoin(ERR_HDX, "newline");
				else
					tmp = ft_strjoin(ERR_HDX, mini->token[i + 1]);
				mini->stx_err_idx = i + 1;
				ft_putstr_fd(tmp, STD_ERR);
				ft_putstr_fd("\n", STD_ERR);
				free(tmp);
				mini->exitcode = EXIT_STX;
				return (FAILURE);
			}
		}
		i++;
	}
	return (SUCCESS);
}
