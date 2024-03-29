/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:43:51 by caguillo          #+#    #+#             */
/*   Updated: 2024/03/30 00:14:54 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

size_t	ft_strlen(char *str)
{
	size_t i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}