/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:53:44 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/02 21:54:37 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct sigaction	t_sigaction;

// SIGINT = ctrl+c
// SIGQUIT = ctrl+\

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
		write(1, "ici\n", 4);
}

void	set_signal_action(void)
{
	t_sigaction	action;

	action = (t_sigaction){0};
	action.sa_handler = &sigint_handler;
	sigaction(SIGINT, &action, NULL);
}

int	main(void)
{
	set_signal_action();
	while (1)
		continue ;
	return (0);
}