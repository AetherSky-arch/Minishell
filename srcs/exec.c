/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:50:16 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/06 01:28:28 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nbr_cmd(t_mini mini, int enum_cmd)
{
	int	i;
	int	nbr;

	if (!(mini.type))
		return (0);
	i = 0;
	nbr = 0;
	while (mini.type[i])
	{
		if (mini.type[i] == enum_cmd)
			nbr++;
		i++;
	}
	return (nbr);
}

void	children(t_mini *mini, char **envp, int nbr_cmd)
{
	int	i;

	i = 0;
	while (i < nbr_cmd)
	{
		if (pipe(mini->fd) == -1)
			perror_close_exit("minishell: pipe", *mini, EXIT_FAILURE);
		else
			child(mini, envp, i);
		i++;
	}
}

void	child(t_mini *mini, char **envp, int k)
{
	(*mini).pid = fork();
	if ((*mini).pid == -1)
		perror_close_exit("minishell: fork", *mini, EXIT_FAILURE);
	if ((*mini).pid == 0)
	{
		// if infile (and the good one) ou heredoc

		// if outfile (and the good one)

		// sinon cas general
		close((*mini).fd[0]);
		if (dup2((*mini).fd[1], STD_OUT) == -1)
			perror_close_exit("pipex: dup2", *mini, EXIT_FAILURE);
		close((*mini).fd[1]);
		exec_arg((*mini), envp, k);
	}
	close((*mini).fd[1]);
	if (dup2((*mini).fd[0], STD_IN) == -1)
		perror_close_exit("pipex: dup2", *mini, EXIT_FAILURE);
	close((*mini).fd[0]);
}