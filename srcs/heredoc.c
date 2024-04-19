/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:31:13 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/19 19:35:31 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// name to be free'd
char	*heredoc_name(void)
{
	char				*name;
	unsigned long int	nbr;
	int					tmp_fd;
	char				*number;

	nbr = 0;
	tmp_fd = -1;
	name = NULL;
	while (nbr < ULONG_MAX)
	{
		number = ft_ulitoa(nbr);
		name = ft_strjoin("/tmp/heredoc_", number);
		free(number);
		if (name)
			tmp_fd = open(name, O_RDWR | O_CREAT | O_EXCL, 0666);
		if (tmp_fd != -1)
			break ;
		nbr++;
	}
	close(tmp_fd);
	return (name);
}

// keep 1023 for a NULL (set at init)
void	open_heredoc(t_mini *mini)
{
	int		i;
	int		fd;
	int		j;	

	i = 0;
	j = 0;
	while (i < mini->type_len)
	{
		if (mini->type[i] == HEREDOC)
		{
			if (mini->token[i + 1])
				mini->lim = mini->token[i + 1];
			while (j < 1023 && mini->hd_name[j])
				j++;
			mini->hd_name[j] = heredoc_name();
			fd = open(mini->hd_name[j], O_RDWR | O_CREAT, 0666);
			if (fd < 0)				
				perror_open(*mini, mini->hd_name[j]);						
			fill_heredoc(mini, fd);
			close(fd);
			//mini->hd_idx++; /***** to be checked here *****/
		}
		i++;
	}
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