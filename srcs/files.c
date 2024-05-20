/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:07:15 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/21 00:07:28 by caguillo         ###   ########.fr       */
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
			if (mini->type[i] == OUTFILE)
				mini->fd_out = open(mini->token[i],
						O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (mini->type[i] == OUTFAPP)
				mini->fd_out = open(mini->token[i],
						O_WRONLY | O_APPEND | O_CREAT, 0666);
			if (mini->fd_out < 0)
				perror_open_free(mini, mini->token[i]);
		}
		i++;
	}
	return (is_outfile);
}

void	check_files(t_mini *mini, int start)
{
	int	i;
	int	tmp_fd;

	i = start;
	tmp_fd = 0;
	while ((i < mini->type_len) && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == INFILE && is_ambigous(mini->token[i]) == 0)
			tmp_fd = open(mini->token[i], O_RDONLY);
		if (mini->type[i] == OUTFILE && is_ambigous(mini->token[i]) == 0)
			tmp_fd = open(mini->token[i], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (mini->type[i] == OUTFAPP && is_ambigous(mini->token[i]) == 0)
			tmp_fd = open(mini->token[i], O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (mini->type[i] == INFILE || mini->type[i] == OUTFILE
			|| mini->type[i] == OUTFAPP)
		{
			if (tmp_fd < 0)
				perror_open_free(mini, mini->token[i]);
			close(tmp_fd);
			free_ambigous(mini, mini->token[i]);
		}
		i++;
	}
}

int	is_ambigous(char *str)
{
	if (!str)
		return (0);
	if (ft_strlen(str) == 1 && str[0] == '*')
		return (1);
	return (0);
}

void	free_ambigous(t_mini *mini, char *str)
{
	if (!str)
		return ;
	if (ft_strlen(str) == 1 && str[0] == '*')
	{
		ft_putstr_fd(ERR_AMB, STD_ERR);
		double_free((void **)mini->hd_name);
		double_free((void **)mini->token);
		double_free((void **)mini->envvars);
		free(mini->fprompt);
		free(mini->type);
		mini->exitcode = EXIT_FAILURE;
		close_exit(*mini, EXIT_FAILURE);
	}
}