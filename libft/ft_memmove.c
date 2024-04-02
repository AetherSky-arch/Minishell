/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:49:05 by arguez            #+#    #+#             */
/*   Updated: 2023/11/08 16:16:42 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	if ((dest == NULL) && (src == NULL))
		return (NULL);
	ptr_dest = dest;
	ptr_src = (unsigned char *)src;
	if (ptr_dest > ptr_src)
	{
		i = n;
		while (i-- > 0)
			ptr_dest[i] = ptr_src[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			ptr_dest[i] = ptr_src[i];
			i++;
		}
	}
	return (dest);
}
