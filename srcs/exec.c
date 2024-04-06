/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:50:16 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/07 01:24:21 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nbr_cmd(t_mini mini)
{
	int	i;
	int	nbr;

	if (!(mini.type))
		return (0);
	i = 0;
	nbr = 0;
	while (mini.type[i])
	{
		if (mini.type[i] == CMD)
			nbr++;
		i++;
	}
	return (nbr);
}

// void	get_cmd_files(t_mini *mini, int *j)
// {
// 	(*mini).is_infile = 0;
// 	(*mini).is_heredoc = 0;
// 	(*mini).is_hd_infile = 0;
// 	(*mini).is_outfile = 0;
// 	(*mini).is_outfapp = 0;
// 	while ((*mini).type[j] && (*mini).type[j] != PIPE)
// 	{
// 		if ((*mini).type[j] == CMD)
// 			(*mini).cmd = (*mini).token[j];
// 		if ((*mini).type[j] == INFILE)
// 		{
// 			(*mini).is_infile = 1;
// 			(*mini).is_hd_infile = 0;
// 			(*mini).in_file = (*mini).token[j];
// 		}
// 		if ((*mini).type[j] == HEREDOC)
// 		{
// 			(*mini).is_hd_infile = 1;
// 			(*mini).is_infile = 0;
// 			(*mini).is_heredoc = 1;
// 			(*mini).lim = (*mini).token[j];
// 		}
// 		if ((*mini).type[j] == OUTFILE)
// 		{
// 			(*mini).is_outfile = 1;
// 			(*mini).is_outfapp = 0;
// 			(*mini).out_file = (*mini).token[j];
// 		}
// 		if ((*mini).type[j] == OUTFAPP)
// 		{
// 			(*mini).is_outfapp = 1;
// 			(*mini).is_outfile = 0;
// 			(*mini).out_fapp = (*mini).token[j];
// 		}
// 		j++;
// 	}
// }

// p_idx = index of the next pipe (so len-1 if no pipe)
// if no pipe (just one cmd), same as usual case,
// the pipe is just not used and closed
void	cmd_to_child(t_mini *mini, char **envp)
{
	int	i;
	int	start;
	int	p_idx;

	i = 0;
	start = 0;
	p_idx = 0;
	while (i < nbr_cmd(*mini))
	{
		while ((*mini).type[p_idx] && (*mini).type[p_idx] != PIPE)
		{
			if ((*mini).type[p_idx] == CMD)
				(*mini).cmd = (*mini).token[p_idx];
			p_idx++;
		}
		if (pipe((*mini).fd) == -1)
			perror_close_exit("minishell: pipe", *mini, EXIT_FAILURE);
		else
			child(mini, envp, start);
		i++;
		if ((*mini).type[p_idx])
			p_idx++;
		start = p_idx;
	}
}

// we need to be sure there is a LIMITER just after HEREDOC (to be checked in STX_ERR)
void	get_heredoc(t_mini *mini, int start)
{
	int	i;

	i = start;
	while ((*mini).type[i] && (*mini).type[i] != PIPE)
	{
		if ((*mini).type[i] == HEREDOC)
		{
			(*mini).is_heredoc = 1;
			(*mini).heredoc_idx = i;
			if ((*mini).token[i + 1])
				(*mini).lim = (*mini).token[i + 1];
			if (pipe((*mini).docfd) == -1)
				perror_close_exit("minishell: pipe", mini, EXIT_FAILURE);
			fill_heredoc(mini);
		}
		i++;
	}
}

int	search_infile(t_mini *mini, int start)
{
	int	i;
	int	is_infile;

	i = start;
	is_infile = 0;
	while ((*mini).type[i] && (*mini).type[i] != PIPE)
	{
		if ((*mini).type[i] == INFILE)
		{
			open_infile(mini, (*mini).token[i]);
			if ((*mini).heredoc_idx < i)
				is_infile = 1;
		}
		i++;
	}
	return (is_infile);
}

// if exist and readable --> open
// else exit (from child)
void	open_infile(t_mini *mini, char *infile)
{
	(*mini).fd_in = open(infile, O_RDONLY);
	if ((*mini).fd_in < 0)
		perror_open(*mini, infile);
}

void	child(t_mini *mini, char **envp, int start)
{
	(*mini).pid = fork();
	if ((*mini).pid == -1)
		perror_close_exit("minishell: fork", *mini, EXIT_FAILURE);
	if ((*mini).pid == 0)
	{
		close((*mini).fd[0]);
		// if infile (and the good one) ou heredoc
		get_heredoc(mini, start);
		if (search_infile(mini, start) == 1)
		{
			dup2((*mini).fd_in, STD_IN);
			close((*mini).fd_in);
		}
		else if ((*mini).is_heredoc == 1)
		{
			dup2((*mini).docfd[0], STD_IN);
			close((*mini).docfd[0]);
		}
		// if outfile (and the good one)
		if (search_outfile(mini, start) == 1)
		{
			// open_outfile(argv[k + 1], pipex);
			dup2((*mini).fd_out, STD_OUT);
			close((*mini).fd_out);
			close((*mini).fd[1]);
		}
		else
		{
			dup2((*mini).fd[1], STD_OUT);
			close((*mini).fd[1]);
		}
		exec_arg(*mini, envp, k);
	}
	close((*mini).fd[1]);
	dup2((*mini).fd[0], STD_IN);
	close((*mini).fd[0]);
}

// perror_close_exit("pipex: dup2", *mini, EXIT_FAILURE);