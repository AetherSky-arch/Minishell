/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_setting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:31:13 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/21 20:19:13 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_heredoc(t_mini *mini)
{
	int	i;
	int	fd;
	int	j;

	i = 0;
	j = 0;
	if (nbr_heredoc(*mini))
	{
		mini->hd_name = create_hd_name(mini);
		while (i < mini->type_len)
		{
			if (mini->type[i] == HEREDOC)
			{
				if (mini->token[i + 1])
					mini->lim = mini->token[i + 1];
				while (mini->hd_name[j])
					j++;
				mini->hd_name[j] = heredoc_name();
				fd = open(mini->hd_name[j], O_RDWR | O_CREAT, 0666);
				if (fd < 0)
					perror_open(*mini, mini->hd_name[j]);
				fill_heredoc(mini, fd);
				close(fd);
			}
			i++;
		}
	}
}

/*************** how to exit in case of failure *****************************/
/*************** how to exit in case of failure *****************************/
/*************** how to exit in case of failure *****************************/
char	**create_hd_name(t_mini *mini)
{
	char	**hd_name;
	int		i;
	int		nb;

	nb = nbr_heredoc(*mini);
	if (nb >= 1024)
	{
		ft_putstr_fd(ERR_NHD, STD_ERR);
		mini->exitcode = EXIT_FAILURE;
		/*****exit****/
		return (NULL);
	}
	hd_name = malloc(sizeof(char *) * (nb + 1));
	if (!hd_name)
		return (NULL);
	/*****malloc error + exit ******/
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

//********** !!! in case of kill, MUST FREE heredoc name ***************//
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
		free(line);
	}
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