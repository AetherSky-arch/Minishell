/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:50:26 by aether            #+#    #+#             */
/*   Updated: 2024/05/20 22:58:14 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_mini *mini)
{
	char	cwd[PATH_MAX];
	
	if (getcwd(cwd, PATH_MAX) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror_close_exit("minishell: getcwd", mini, EXIT_FAILURE);
	return (0);
}

// if (args != NULL)
// 		return (ft_putstr_fd("minishell: pwd: too many arguments\n", STD_ERR),
// 			1);