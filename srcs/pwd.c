/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:50:26 by aether            #+#    #+#             */
/*   Updated: 2024/04/27 00:17:19 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(char **args)
{
	char	cwd[PATH_MAX];

	if (args != NULL)
		return (ft_putstr_fd("minishell: pwd: too many arguments\n", STD_ERR),
			1);
	if (getcwd(cwd, PATH_MAX) != NULL)
		ft_printf("%s\n", cwd);
	else
		return (ft_putstr_fd("minishell: pwd: getcwd() error\n", STD_ERR), 1);
	return (0);
}
