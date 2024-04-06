/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:03:17 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/07 00:30:29 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_exit(t_mini mini, int k)
{
	close(mini.fd_in);
	close(mini.fd_out);
	close(mini.fd[0]);
	close(mini.fd[1]);
    close(mini.docfd[0]);
	close(mini.docfd[1]);
	exit(k);
}

void	perror_close_exit(char *err, t_mini mini, int k)
{
	perror(err);
	close_exit(mini, k);
}

void	perror_open(t_mini mini, char *filename)
{
	char *tmp;

	tmp = ft_strjoin("minishell: ", filename);
	perror(tmp);
	free(tmp);
	close(mini.fd_in);
	close(mini.fd_out);
	close(mini.fd[0]);
	close(mini.fd[1]);
	exit(EXIT_FAILURE);
}