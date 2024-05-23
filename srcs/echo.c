/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:50:33 by aether            #+#    #+#             */
/*   Updated: 2024/05/23 20:58:00 by caguillo         ###   ########.fr       */
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
