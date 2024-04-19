/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:38:30 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/19 00:42:20 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	len_nbr(unsigned long int n);
static char		*fill_nbr(char *nbr, size_t size, unsigned long int n);

char	*ft_ulitoa(unsigned long int n)
{
	char	*nbr;
	size_t	size;

	size = len_nbr(n);
	nbr = malloc(sizeof(char) * (size + 1));
	if (!nbr)
		return (NULL);
	return (fill_nbr(nbr, size, n));
}

static char	*fill_nbr(char *nbr, size_t size, unsigned long int n)
{
	nbr[size] = '\0';
	if (n == 0)
		nbr[size - 1] = 48;
	else
	{
		while (n >= 1)
		{
			size--;
			nbr[size] = n % 10 + 48;
			n = n / 10;
		}
	}
	return (nbr);
}

static size_t	len_nbr(unsigned long int n)
{
	size_t	size;

	size = 1;
	while ((n / 10) >= 1)
	{
		size++;
		n = n / 10;
	}
	return (size);
}
