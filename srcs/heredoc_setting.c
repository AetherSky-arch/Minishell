/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_setting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:31:13 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/08 22:03:13 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// << | << eof = stx_err vs << eof | << = open before stx_err
// nbr_heredoc(*mini)
void	open_heredoc(t_mini *mini, int nbr_hd)
{
	int	i;
	int	fd;
	int	j;

	i = 0;
	j = 0;
	if (nbr_hd)
	{
		mini->hd_name = create_hd_name(mini);
		if (mini->hd_name)
		{
			while ((i < mini->type_len - 1) && (g_exitcode != 130))
			{
				if (mini->type[i] == HEREDOC && mini->type[i + 1] == LIMITER
					&& j < nbr_hd)
				{
					if (mini->token[i + 1])
						mini->lim = mini->token[i + 1];
					mini->hd_name[j] = heredoc_name();
					fd = open(mini->hd_name[j], O_RDWR | O_CREAT, 0666);
					if (fd < 0)
						perror_open_free(mini, mini->hd_name[j]);
					fill_heredoc(mini, fd);
					close(fd);
					while (mini->hd_name[j])
						j++;
				}
				i++;
			}
		}
	}
}

char	**create_hd_name(t_mini *mini)
{
	char	**hd_name;
	int		i;
	int		nb;

	nb = nbr_heredoc(*mini);
	if (nb > 16)
	{
		ft_putstr_fd(ERR_NHD, STD_ERR);
		free_close_exit(mini, EXIT_STX, 0);
	}
	hd_name = malloc(sizeof(char *) * (nb + 1));
	if (!hd_name)
	{
		ft_putstr_fd(ERR_MAL, STD_ERR);
		return (mini->exitcode = EXIT_FAILURE, NULL);
	}
	i = 0;
	while (i < nb)
	{
		hd_name[i] = NULL;
		i++;
	}
	hd_name[i] = NULL;
	return (hd_name);
}

// name to be free'd
char	*heredoc_name(void)
{
	char				*name;
	unsigned long int	nbr;
	char				*number;

	nbr = 0;
	name = NULL;
	while (nbr < ULONG_MAX)
	{
		number = ft_ulitoa(nbr);
		name = ft_strjoin("/tmp/heredoc_", number);
		free(number);
		if (name)
		{
			if (access(name, F_OK) != 0)
				break ;
		}
		nbr++;
		free(name);
	}
	return (name);
}

void	fill_heredoc(t_mini *mini, int fd)
{
	char	*line;
	char	*limiter;
	int		save_in;

	g_exitcode = 0;
	save_in = dup(STD_IN);
	signal(SIGINT, &handle_sigint_in_hd);
	//
	limiter = ft_strjoin((*mini).lim, "\n");
	if (!limiter)
		limiter_err_mal(*mini);
	//
	while (g_exitcode != 130)
	{
		line = readline("> ");
		// ft_putstr_fd("> ", STD_IN);
		// line = get_next_line(STD_IN);
		if (!line && g_exitcode == 130)
		{
			dup2(save_in, STD_IN);
			close(save_in);
		}
		else if (!line)
		{
			// ft_putstr_fd(ERR_GNL, STD_ERR);
			ft_putstr_fd(ERR_RDL, STD_ERR); // Modify text ??? --> ctrl+d
			break ;
		}
		// else if (ft_strcmp(line, limiter) == 0)
		else if (ft_strcmp(line, (*mini).lim) == 0)
			break ;
		else if (ft_strcmp(line, "") == 0)
			ft_putstr_fd("\n", fd);
		else
			ft_putstr_fd(line, fd);
		free(line);
	}
	close(save_in);
	free(line);
	free(limiter);
}

void	limiter_err_mal(t_mini mini)
{
	ft_putstr_fd(ERR_MAL, STD_ERR);
	close_exit(mini, EXIT_FAILURE);
}

/***draft ****/

// int					tmp_fd;
// tmp_fd = -1;
// if (name)
// 	tmp_fd = open(name, O_RDWR | O_CREAT | O_EXCL, 0666);
// if (tmp_fd != -1)
// 	break ;
// close(tmp_fd);
