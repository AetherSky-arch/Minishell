/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 03:00:18 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/29 17:14:03 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_exitcode(t_mini *mini)
{
	pid_t	tmp;

	while (1)
	{
		tmp = wait(&((*mini).status));
		if (tmp == -1)
			break ;
		if (tmp == (*mini).last_pid)
		{
			if (WIFEXITED((*mini).status))
			{
				(*mini).exitcode = WEXITSTATUS((*mini).status);
			}
			else
				(*mini).exitcode = 128 + WTERMSIG((*mini).status);
		}
	}
}
