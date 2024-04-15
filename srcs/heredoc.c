/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:31:13 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/16 01:22:42 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/****** limiter: to be free'd ?????????******/
void	open_heredoc(t_mini *mini)
{
	int	i;
	int	fd;
	int	j;

	i = 0;
	while (i < mini->type_len)
	{
		if (mini->type[i] == HEREDOC)
		{
			if (mini->token[i + 1])
				mini->lim = mini->token[i + 1];
			//fd = open(".", O_TMPFILE | O_RDWR, 0666);
			fd = open("/tmp", O_TMPFILE | O_RDWR, 0666);			
			ft_putstr_fd("fd=", STD_ERR);
			ft_putnbr_fd(fd, STD_ERR);
			ft_putstr_fd("\n", STD_ERR);
			if (fd < 0)
				perror_open(*mini, "here_doc");
			j = 0;
			while (mini->hd_fd[j] != 0)
				j++;
			mini->hd_fd[j] = fd;
			fill_heredoc(mini, fd);
		}
		i++;
	}
}

void	fill_heredoc(t_mini *mini, int fd)
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
			ft_putstr_fd(line, fd);
		// ft_putstr_fd(line, (*mini).docfd[1]);
		free(line);
	}
	free(line);
	free(limiter);
	// close((*mini).docfd[1]);	
}

void	limiter_err_mal(t_mini mini)
{
	ft_putstr_fd(ERR_MAL, STD_ERR);
	close_exit(mini, EXIT_FAILURE);
}