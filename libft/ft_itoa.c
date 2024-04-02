/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: arguez <marvin@42.fr>			    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/11/08 13:52:57 by arguez	       #+#    #+#	      */
/*   Updated: 2023/11/09 21:11:39 by arguez           ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	digits;

	digits = 0;
	if (n < 0)
	{
		n = -n;
		digits++;
	}
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

static void	ft_putnbr(int nb, char *str, int *i)
{
	unsigned int	new;

	if (nb < 0)
	{
		str[*i] = '-';
		new = -nb;
		*i = *i + 1;
	}
	else
		new = nb;
	if (new >= 10)
	{
		ft_putnbr(new / 10, str, i);
		*i = *i + 1;
		ft_putnbr(new % 10, str, i);
	}
	else
		str[*i++] = new + 48;
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;

	if (n == 0)
	{
		str = (char *) malloc (2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = (char *) malloc (count_digits(n) + 1);
	if (!str)
		return (NULL);
	i = 0;
	ft_putnbr(n, str, &i);
	i = i + 1;
	str[i] = '\0';
	return (str);
}
