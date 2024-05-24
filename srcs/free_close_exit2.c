/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_exit2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:28:28 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/24 01:34:21 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	perr_cl_ex_save(char *err, t_mini *mini, int k, int save_fd)
{
	close(save_fd);
	perror_close_exit(err, mini, k);
}
