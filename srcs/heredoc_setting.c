/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_setting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:31:13 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/29 00:10:07 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	name_open_fill_hd(t_mini *mini, int i, int *j)
{
	int	fd;

	if (mini->token[i + 1])
		mini->lim = mini->token[i + 1];
	mini->hd_name[*j] = heredoc_name();
	fd = open(mini->hd_name[*j], O_RDWR | O_CREAT, 0666);
	if (fd < 0)
		perror_open_free(mini, mini->hd_name[*j]);
	fill_heredoc(mini, fd);
	close(fd);
	while (mini->hd_name[*j])
		*j = *j + 1;
}

// << | << eof = stx_err vs << eof | << = open before stx_err
// nbr_heredoc(*mini)
void	open_heredoc(t_mini *mini, int nbr_hd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!nbr_hd)
		return ;
	mini->hd_name = create_hd_name(mini);
	if (mini->hd_name)
	{
		while ((i < mini->type_len - 1) && (g_exitcode != 130))
		{
			if (mini->type[i] == HEREDOC && mini->type[i + 1] == LIMITER
				&& j < nbr_hd)
			{
				name_open_fill_hd(mini, i, &j);
			}
			i++;
		}
	}
}

static void	fill_hd_save_in(t_mini *mini, int *save_in)
{
	*save_in = dup(STD_IN);
	if (*save_in == -1)
		perror_close_exit("minishell: dup", mini, EXIT_FAILURE);
}

static void	fill_hd_get_in(t_mini *mini, int *save_in)
{
	if (dup2(*save_in, STD_IN) == -1)
		perr_cl_ex_save("minishell: dup2", mini, EXIT_FAILURE, *save_in);
	close(*save_in);
}

void	fill_heredoc(t_mini *mini, int fd)
{
	char	*line;
	int		save_in;

	g_exitcode = 0;
	fill_hd_save_in(mini, &save_in);
	signal(SIGINT, &handle_sigint_in_hd);
	while (g_exitcode != 130)
	{
		line = readline("> ");
		if (!line && g_exitcode == 130)
			fill_hd_get_in(mini, &save_in);
		else if (!line)
		{
			ft_putstr_fd(ERR_RHD, STD_ERR);
			break ;
		}
		else if (ft_strcmp(line, (*mini).lim) == 0)
			break ;
		else
			(ft_putstr_fd(line, fd), ft_putstr_fd("\n", fd));
		free(line);
	}
	(close(save_in), free(line));
}

/***draft GNL ****/

// char	*limiter;
// //
// limiter = ft_strjoin((*mini).lim, "\n");
// if (!limiter)
// 	limiter_err_mal(*mini);
// //
// free(limiter);

// ft_putstr_fd("> ", STD_IN);
// line = get_next_line(STD_IN);
// ft_putstr_fd(ERR_GNL, STD_ERR);
// else if (ft_strcmp(line, limiter) == 0)
// else if (ft_strcmp(line, "") == 0)
// 	ft_putstr_fd("\n", fd);

// void	limiter_err_mal(t_mini mini)
// {
// 	ft_putstr_fd(ERR_MAL, STD_ERR);
// 	free_close_exit(&mini, EXIT_FAILURE, 0);
// }
