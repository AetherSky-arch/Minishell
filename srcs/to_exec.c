/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:50:16 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/17 02:00:57 by caguillo         ###   ########.fr       */
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

void	re_init_mini(t_mini *mini)
{
	mini->is_pipe = 0;
	mini->is_last_pid = 0;
	// mini->prev_fd0 = -1;
	mini->prev_fd0 = 0;
}

void	close_prev_pipe(t_mini mini)
{
	if (mini.prev_fd0 > 0)
		close(mini.prev_fd0);
}

// j = index of the next pipe (so len-1 if no pipe)
// if no pipe (just one cmd), same as usual case,
// the pipe is just not used and closed
void	blocks_to_child(t_mini *mini, char **envp, int nbr_cmd)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	start = 0;
	j = 0;
	while (i < nbr_cmd)
	{
		while ((j < mini->type_len) && (mini->type[j] != PIPE))
			j++;
		if (j == mini->type_len)
		{
			mini->is_last_pid = 1;
			mini->is_pipe = 0;
		}
		else if (mini->type[j] == PIPE)
			mini->is_pipe = 1;
		if (pipe(mini->fd) == -1)
			perror_close_exit("minishell: pipe", *mini, EXIT_FAILURE);
		else
			child(mini, envp, start);
		if (j < mini->type_len)
			j++;
		start = j;
		i++;
	}
}

// we need to be sure there is a LIMITER just after HEREDOC (to be checked in STX_ERR)
void	get_heredoc(t_mini *mini, int start)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	mini->is_heredoc = 0;
	while ((i < mini->type_len) && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == HEREDOC)
		{
			mini->is_heredoc = 1;
			mini->heredoc_idx = i;
			if (mini->heredoc_fd > 0)
			{
				while (j < 1024 && (mini->heredoc_fd != mini->hd_fd[j]))
					j++;
				close(mini->heredoc_fd);
				mini->heredoc_fd = mini->hd_fd[j + 1];
			}
			else
				mini->heredoc_fd = mini->hd_fd[0];
		}
		i++;
	}
}

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
			if (mini->heredoc_idx < i)
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
		perror_open(*mini, infile);
}

int	is_outfile(t_mini *mini, int start)
{
	int	i;
	int	is_outfile;

	i = start;
	is_outfile = 0;
	while ((i < mini->type_len) && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == OUTFILE)
		{
			mini->fd_out = open(mini->token[i], O_WRONLY | O_TRUNC | O_CREAT,
					0666);
			is_outfile = 1;
		}
		if (mini->type[i] == OUTFAPP)
		{
			mini->fd_out = open(mini->token[i], O_WRONLY | O_APPEND | O_CREAT,
					0666);
			is_outfile = 1;
		}
		if (mini->fd_out < 0)
			perror_open(*mini, mini->token[i]);
		i++;
	}
	return (is_outfile);
}

void	child(t_mini *mini, char **envp, int start)
{
	pid_t	pid;
	// char buff[42];
	// ssize_t n;

	get_heredoc(mini, start);
	// n = read(mini->heredoc_fd, buff, 42);
	// ft_putnbr_fd(n, STD_ERR);
	// ft_putstr_fd(buff, STD_ERR);
	// ft_putstr_fd("heredoc fd=", STD_ERR);
	// ft_putnbr_fd(mini->heredoc_fd, STD_ERR);
	// ft_putstr_fd("\n", STD_ERR);
	pid = fork();
	if (mini->is_last_pid == 1)
		mini->last_pid = pid;
	if (pid == -1)
		perror_close_exit("minishell: fork", *mini, EXIT_FAILURE);
	if (pid == 0)
	{
		close(mini->fd[0]);
		// if infile (and the good one) or heredoc or the pipe of the previous cmd
		if (is_infile(mini, start) == 1)
		{
			dup2(mini->fd_in, STD_IN);
			close(mini->fd_in);
		}
		else if (mini->is_heredoc == 1)
		{
			dup2(mini->heredoc_fd, STD_IN);
			close(mini->heredoc_fd);
			// ft_putstr_fd("c heredoc fd=", STD_ERR);
			// ft_putnbr_fd(mini->heredoc_fd, STD_ERR);
			// ft_putstr_fd("\n", STD_ERR);
		}
		else if (mini->prev_fd0 > 0)
			dup2(mini->prev_fd0, STD_IN);
		if (mini->prev_fd0 > 0)
			close(mini->prev_fd0);
		// if outfile (and the good one)
		if (is_outfile(mini, start) == 1)
		{
			dup2(mini->fd_out, STD_OUT);
			close(mini->fd_out);
		}
		else if (mini->is_pipe == 1)
			dup2(mini->fd[1], STD_OUT);
		close(mini->fd[1]);
		exec_arg(*mini, envp, start);
	}
	if (mini->heredoc_fd > 0)
	 	close(mini->heredoc_fd);
	close(mini->fd[1]);
	if (mini->prev_fd0 > 0)
		close(mini->prev_fd0);
	mini->prev_fd0 = dup(mini->fd[0]);
	close(mini->fd[0]);
}

// ft_putstr_fd("pipe OUT", STD_ERR);
// ft_putnbr_fd(start, STD_ERR);
// perror_close_exit("pipex: dup2", *mini, EXIT_FAILURE);

// // forcely something else after a pipe otherwise Stx Error
// void	fill_pipe(t_mini *mini, int next_block)
// {
// 	int	i;

// 	mini->fill_pipe = 1;
// 	i = next_block;
// 	while ((i < mini->type_len) && (mini->type[i] != PIPE))
// 	{
// 		if ((mini->type[i] == INFILE) || (mini->type[i] == HEREDOC))
// 		{
// 			mini->fill_pipe = 0;
// 			break ;
// 		}
// 		i++;
// 	}
// }

// printf("OUT=%d\n", fcntl(mini->fd[1], F_GETFL));
// printf("OUTgnl=%d\n", fcntl(STD_OUT, F_GETFL));
// printf("INgnl=%d\n", fcntl(STD_IN, F_GETFL));

// void	blocks_to_child(t_mini *mini, char **envp, int nbr_cmd, int do_heredoc)
// {
// 	int	i;
// 	int	start;
// 	int	j;

// 	i = 0;
// 	start = 0;
// 	j = 0;
// 	while (i < nbr_cmd)
// 	{
// 		mini->is_heredoc = 0;
// 		while ((j < mini->type_len) && (mini->type[j] != PIPE))
// 		{
// 			if (mini->type[j] == HEREDOC)
// 				mini->is_heredoc = 1;
// 			j++;
// 		}
// 		if (j == mini->type_len)
// 		{
// 			mini->is_last_pid = 1;
// 			mini->is_pipe = 0;
// 		}
// 		else if (mini->type[j] == PIPE)
// 			mini->is_pipe = 1;
// 		if (pipe(mini->fd) == -1)
// 			perror_close_exit("minishell: pipe", *mini, EXIT_FAILURE);
// 		else
// 		{
// 			if (mini->is_heredoc == do_heredoc)
// 				child(mini, envp, start);
// 		}
// 		i++;
// 		if (j < mini->type_len)
// 			j++;
// 		start = j;
// 	}
// }
