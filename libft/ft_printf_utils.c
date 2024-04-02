/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:39:50 by arguez            #+#    #+#             */
/*   Updated: 2024/03/01 17:23:51 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digits(int n)
{
	int	counter;

	if (n == 0)
		return (1);
	counter = 0;
	if (n < 0)
	{
		n = n * -1;
		counter++;
	}
	while (n != 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

int	ft_numput(int n, int fd)
{
	ft_putnbr_fd(n, fd);
	return (count_digits(n));
}
