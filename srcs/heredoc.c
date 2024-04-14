/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:31:13 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/15 01:33:27 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/****** limiter: to be free'd ?????????******/
void	open_heredoc(t_mini *mini)
{
	int	i;
	int	fd;

	i = 0;
	while ((i < mini->type_len)) // && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == HEREDOC)
		{
			if (mini->token[i + 1])
				mini->lim = mini->token[i + 1];
			fd = open(".", O_TMPFILE | O_RDWR);
			if (fd < 0)
				perror_open(*mini, "here_doc");
			/****** update tab des fd 'entier*******/
			// dans l'exec des cmd si here_doc => aller chercher son fd,
			//	puis traiter comme un infile
			fill_heredoc(mini);
		}
		i++;
	}
}

void	fill_heredoc(t_mini *mini)
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin((*mini).lim, "\n");
	if (!limiter)
		limiter_err_mal(*mini);
	while (1)
	{
		ft_putstr_fd("> ", STD_IN);
		line = get_next_line(STD_IN);
		if (!line)
		{
			ft_putstr_fd(ERR_GNL, STD_ERR);
			close_exit(*mini, EXIT_FAILURE);
		}
		if (ft_strcmp(line, limiter) == 0)
			break ;
		else
			ft_putstr_fd(line, (*mini).docfd[1]);
		free(line);
	}
	free(line);
	free(limiter);
	close((*mini).docfd[1]);
}

void	limiter_err_mal(t_mini mini)
{
	ft_putstr_fd(ERR_MAL, STD_ERR);
	close_exit(mini, EXIT_FAILURE);
}