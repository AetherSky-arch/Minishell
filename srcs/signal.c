/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:53:44 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/05 01:45:44 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * SIGINT = ctrl+c
 * SIGQUIT = ctrl+\
 * ctrl+d = not a signal
 */

void	signal_handler(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handler(int signal)
{
	(void)signal;
	g_exitcode = 130;
	write(1, "\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
}

void	signal_handler_in_child(void)
{
	signal(SIGINT, &sigint_handler_in_child);
	signal(SIGQUIT, SIG_IGN);
}

// do nothing but not ignore it
void	sigint_handler_in_child(int signal)
{
	(void)signal;
}
