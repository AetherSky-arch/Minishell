/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:33:30 by arguez            #+#    #+#             */
/*   Updated: 2023/11/28 17:47:13 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	picker(char c, va_list list)
{
	int	plen;

	plen = 0;
	if (c == 'c')
		plen += ft_putchar_fd(va_arg(list, int), 1);
	else if (c == 's')
		plen += ft_putstr_fd(va_arg(list, char *), 1);
	else if (c == 'p')
		plen += ft_putptr((uintptr_t)va_arg(list, void *), 'x') + 2;
	else if (c == 'i')
		plen += ft_numput(va_arg(list, int), 1);
	else if (c == 'd')
		plen += ft_numput(va_arg(list, int), 1);
	else if (c == 'u')
		plen += ft_putunsigned(va_arg(list, unsigned int));
	else if (c == 'x')
		plen += ft_hexput(va_arg(list, unsigned int), c);
	else if (c == 'X')
		plen += ft_hexput(va_arg(list, unsigned int), c);
	else if (c == '%')
		plen += ft_putchar_fd('%', 1);
	return (plen);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	if (!format)
		return (0);
	va_start(list, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			counter += picker(format[i + 1], list);
			i = i + 2;
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			counter++;
			i++;
		}
	}
	va_end(list);
	return (counter);
}
