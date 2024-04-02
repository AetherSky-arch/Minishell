/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:17:35 by arguez            #+#    #+#             */
/*   Updated: 2023/11/13 16:35:29 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char			*ptr;
	unsigned int			i;

	if ((c == 0) && (n == 0))
		return (NULL);
	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)c == ptr[i])
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}
