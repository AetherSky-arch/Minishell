/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:50:33 by aether            #+#    #+#             */
/*   Updated: 2024/05/20 21:27:47 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_noline_option(char *str)
{
	int	i;

	if (!str)
		return (FALSE);
	if (str[0] != '-')
		return (FALSE);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	if (i == 1)
		return (FALSE);
	return (TRUE);
}

// args = cmd_arg = CMD / ARG / ARG ...
int	ft_echo(char **args)
{
	int	i;

	if ((args == NULL) || (args[0] == NULL))
		return (FAILURE);
	if (args[1] == NULL)
		return (ft_printf("\n"), SUCCESS);
	i = 1;
	while (args[i] && is_noline_option(args[i]) == TRUE)
		i++;
	while (args[i] != NULL)
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (is_noline_option(args[1]) == FALSE)
		ft_printf("\n");
	return (SUCCESS);
}

// static int	with_newline(char **args)
// {
// 	int	i;

// 	i = 0;
// 	while (args[i] != NULL)
// 	{
// 		if (ft_strcmp(args[i], "-n") == 0)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// static char	*get_next_arg(char **args, int i)
// {
// 	char	*next;

// 	next = args[i + 1];
// 	if (next == NULL)
// 		return (NULL);
// 	if (ft_strcmp(next, "-n") != 0)
// 		return (next);
// 	next = args[i + 2];
// 	if (next != NULL)
// 		return (next);
// 	return (NULL);
// }
