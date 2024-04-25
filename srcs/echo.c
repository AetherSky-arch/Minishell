/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:50:33 by aether            #+#    #+#             */
/*   Updated: 2024/04/25 23:05:45 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	with_newline(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], "-n") == 0)
			return (0);
		i++;
	}
	return (1);
}

static char	*get_next_arg(char **args, int i)
{
	char	*next;

	next = args[i + 1];
	if (next == NULL)
		return (NULL);
	if (ft_strcmp(next, "-n") != 0)
		return (next);
	next = args[i + 2];
	if (next != NULL)
		return (next);
	return (NULL);
}

int	echo(char **args)
{
	int	i;

	args++;
	if ((args == NULL) || (args[0] == NULL))
		return (1);
	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], "-n") != 0)
		{
			ft_printf(args[i]);
			if (get_next_arg(args, i) != NULL)
				ft_printf(" ");
		}
		i++;
	}
	if (with_newline(args))
		ft_printf("\n");
	return (0);
}
