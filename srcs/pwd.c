/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:50:26 by aether            #+#    #+#             */
/*   Updated: 2024/04/10 20:02:15 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(char **args)
{
	char	cwd[PATH_MAX];

	if (args != NULL)
		return (ft_putstr_fd("pwd: too many arguments\n", 2), 1);
	if (getcwd(cwd, PATH_MAX) != NULL)
		ft_printf("%s\n", cwd);
	else
		return (ft_putstr_fd("pwd: getcwd() error\n", 2), 1);
	return (0);
}
