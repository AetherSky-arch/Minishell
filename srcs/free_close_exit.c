/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:03:17 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/18 03:45:00 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_exit(t_mini mini, int k)
{
	close(mini.fd_in);
	close(mini.fd_out);
	close(mini.fd[0]);
	close(mini.fd[1]);
	// close(mini.docfd[0]);
	// close(mini.docfd[1]);
	close(mini.hd_fd);
	close(mini.prev_fd0);
	exit(k);
}

void	perror_close_exit(char *err, t_mini mini, int k)
{
	perror(err);
	close_exit(mini, k);
}

void	perror_open(t_mini mini, char *filename)
{
	char	*tmp;

	tmp = ft_strjoin("minishell: ", filename);
	perror(tmp);
	free(tmp);
	close_exit(mini, EXIT_FAILURE);
}

void	free_close_exit(t_mini *mini, int exit_code, int is_paths)
{
	double_free((void **)(*mini).cmd_arg);
	if (is_paths == 1)
		double_free((void **)(*mini).paths);
	close_exit(*mini, exit_code);
}

void	putstr_error(char *cmd0, char *err_str)
{
	char *tmp1;
	char *tmp2;

	tmp1 = ft_strjoin("minishell: ", cmd0);
	tmp2 = ft_strjoin(tmp1, err_str);
	ft_putstr_fd(tmp2, STD_ERR);
	free(tmp1);
	free(tmp2);
}