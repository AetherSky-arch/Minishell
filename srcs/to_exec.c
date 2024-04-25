/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:50:16 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/26 01:28:14 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nbr_block(t_mini mini)
{
	int	i;
	int	nbr;

	if (!(mini.type))
		return (0);
	i = 0;
	nbr = 1;
	while (i < mini.type_len)
	{
		if (mini.type[i] == PIPE)
			nbr++;
		i++;
	}
	return (nbr);
}

// j = index of the next pipe (so len-1 if no pipe)
// if no pipe (just one cmd or heredoc), same as usual case,
// the pipe is just not used and closed
void	blocks_to_exec(t_mini *mini, char **envp, int nbr_block)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	start = 0;
	j = 0;
	while (i < nbr_block)
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
			perror_close_exit("minishell: pipe", mini, EXIT_FAILURE);
		else if (is_builtin(*mini, start) != -1)
		{
			parent(mini, create_block(mini, start), start);
		}
		else
			child(mini, envp, start);
		if (j < mini->type_len)
			j++;
		start = j;
		i++;
	}
}

void	child(t_mini *mini, char **envp, int start)
{
	pid_t	pid;

	get_heredoc(mini, start);
	pid = fork();
	if (mini->is_last_pid == 1)
		mini->last_pid = pid;
	if (pid == -1)
		perror_close_exit("minishell: fork", mini, EXIT_FAILURE);
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
			dup2(mini->hd_fd, STD_IN);
			close(mini->hd_fd);
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
	close(mini->fd[1]);
	if (mini->prev_fd0 > 0)
		close(mini->prev_fd0);
	mini->prev_fd0 = dup(mini->fd[0]);
	close(mini->fd[0]);
}

void	close_prev_pipe(t_mini mini)
{
	if (mini.prev_fd0 > 0)
		close(mini.prev_fd0);
	if (mini.hd_fd > 0)
		close(mini.hd_fd);
}

/****draft ******/

// perror_close_exit("pipex: dup2", *mini, EXIT_FAILURE);
// // forcely something else after a pipe otherwise Stx Error

// ft_putstr_fd("start=", STD_ERR);
// ft_putnbr_fd(start, STD_ERR);
// ft_putstr_fd("\n", STD_ERR);
// ft_putstr_fd("is hd=", STD_ERR);
// ft_putnbr_fd(mini->is_heredoc, STD_ERR);
// ft_putstr_fd("\n", STD_ERR);
// ft_putstr_fd("heredoc fd=", STD_ERR);
// ft_putnbr_fd(mini->hd_fd, STD_ERR);
// ft_putstr_fd("\n", STD_ERR);
// ft_putstr_fd("idx=", STD_ERR);
// ft_putnbr_fd(mini->hd_idx, STD_ERR);
// ft_putstr_fd("\n", STD_ERR);
// ft_putstr_fd("is pipe + start=", STD_ERR);
// ft_putnbr_fd(mini->is_pipe + start, STD_ERR);
// ft_putstr_fd("\n", STD_ERR);
// ft_putstr_fd("get fd=", STD_ERR);
// ft_putnbr_fd(mini->hd_fd, STD_ERR);
// ft_putstr_fd("\n", STD_ERR);

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

// void	re_init_mini(t_mini *mini)
// {
// 	mini->is_pipe = 0;
// 	mini->is_last_pid = 0;
// 	// mini->prev_fd0 = -1;
// 	mini->prev_fd0 = 0;
// }