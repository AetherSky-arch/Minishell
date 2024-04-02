/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointers_converter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:22:29 by arguez            #+#    #+#             */
/*   Updated: 2023/11/28 18:28:56 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(uintptr_t n, char format)
{
	if ((void *)n == (void *)0)
	{
		ft_putstr_fd("(nil)", 1);
		return (3);
	}
	if ((long)n == LONG_MIN)
	{
		ft_putstr_fd("0x8000000000000000", 1);
		return (16);
	}
	if ((unsigned long)n == ULONG_MAX)
	{
		ft_putstr_fd("0xffffffffffffffff", 1);
		return (16);
	}
	ft_putstr_fd("0x", 1);
	return (ft_hexput(n, format));
}
