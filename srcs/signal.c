/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:53:44 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/23 22:47:44 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * SIGINT = ctrl+c
 * SIGQUIT = ctrl+\
 * ctrl+d = not a signal
 */

void	manage_signal(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint(int signal)
{
	(void)signal;
	g_exitcode = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// do nothing but not ignore it
void	handle_sigint_in_child(int signal)
{
	(void)signal;
}

void	handle_sigint_in_hd(int signal)
{
	(void)signal;
	close(STD_IN);
	g_exitcode = 130;
	write(1, "\n", 1);
}
