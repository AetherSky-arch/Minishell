/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:50:16 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/09 01:37:49 by caguillo         ###   ########.fr       */
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
	while (i < mini.type_len)
	{
		if (mini.type[i] == CMD)
			nbr++;
		i++;
	}
	return (nbr);
}

/*******************************************************************/
/***************** should be at least one CMD by defaults, yes ??? */
/*******************************************************************/
// j = index of the ne// printf("%d\n", nbr);xt pipe (so len-1 if no pipe)
// if no pipe (just one cmd), same as usual case,
// the pipe is just not used and closed
void	block_to_child(t_mini *mini, char **envp)
{
	int	i;
	int	start;
	int	j;
	int	nbr;

	i = 0;
	start = 0;
	j = 0;
	nbr = nbr_cmd(*mini);
	// (*mini).is_pipe = 0;
	(*mini).is_last_pid = 0;
	while (i < nbr)
	{
		while ((j < (*mini).type_len) && (*mini).type[j] != PIPE)
			j++;
		if (j == (*mini).type_len)
		{
			(*mini).is_last_pid = 1;
			(*mini).is_pipe = 0;
		}
		else if ((*mini).type[j] == PIPE)
			(*mini).is_pipe = 1;
		if (pipe((*mini).fd) == -1)
			perror_close_exit("minishell: pipe", *mini, EXIT_FAILURE);
		else
			child(mini, envp, start);
		i++;
		if (j < (*mini).type_len)
			j++;
		start = j;
	}
}

// we need to be sure there is a LIMITER just after HEREDOC (to be checked in STX_ERR)
void	get_heredoc(t_mini *mini, int start)
{
	int	i;

	i = start;
	while ((i < (*mini).type_len) && (*mini).type[i] != PIPE)
	{
		if ((*mini).type[i] == HEREDOC)
		{
			(*mini).is_heredoc = 1;
			(*mini).heredoc_idx = i;
			if ((*mini).token[i + 1])
				(*mini).lim = (*mini).token[i + 1];
			if (pipe((*mini).docfd) == -1)
				perror_close_exit("minishell: pipe", *mini, EXIT_FAILURE);
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
	while ((i < (*mini).type_len) && (*mini).type[i] != PIPE)
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

int	search_outfile(t_mini *mini, int start)
{
	int	i;
	int	is_outfile;

	i = start;
	is_outfile = 0;
	while ((i < (*mini).type_len) && (*mini).type[i] != PIPE)
	{
		if ((*mini).type[i] == OUTFILE)
		{
			(*mini).fd_out = open((*mini).token[i],
					O_WRONLY | O_TRUNC | O_CREAT, 0666);
			is_outfile = 1;
		}
		if ((*mini).type[i] == OUTFAPP)
		{
			(*mini).fd_out = open((*mini).token[i],
					O_WRONLY | O_APPEND | O_CREAT, 0666);
			is_outfile = 1;
		}
		if ((*mini).fd_out < 0)
			perror_open(*mini, (*mini).token[i]);
		i++;
	}
	return (is_outfile);
}

void	child(t_mini *mini, char **envp, int start)
{
	pid_t	pid;

	pid = fork();
	if ((*mini).is_last_pid == 1)
		(*mini).pid = pid;
	if (pid == -1)
		perror_close_exit("minishell: fork", *mini, EXIT_FAILURE);
	if (pid == 0)
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
			dup2((*mini).fd_out, STD_OUT);
			close((*mini).fd_out);
			close((*mini).fd[1]);
		}
		else if ((*mini).is_pipe == 1)
		{
			dup2((*mini).fd[1], STD_OUT);
			close((*mini).fd[1]);
		}
		exec_arg(*mini, envp, start);
	}
	close((*mini).fd[1]);
	if ((*mini).is_pipe == 1)
	{
		dup2((*mini).fd[0], STD_IN);
		close((*mini).fd[0]);
	}
}

// perror_close_exit("pipex: dup2", *mini, EXIT_FAILURE);

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