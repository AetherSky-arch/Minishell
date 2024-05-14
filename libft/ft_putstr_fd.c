/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:41:57 by arguez            #+#    #+#             */
/*   Updated: 2024/05/14 22:48:06 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_putstr_fd("(null)", fd);
int	ft_putstr_fd(char *str, int fd)
{
	int	i;

	if (!str)
	{
		return (6);
	}
	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
	return (i);
}
