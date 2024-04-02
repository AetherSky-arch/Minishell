/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: arguez <marvin@42.fr>			    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/11/06 16:00:03 by arguez	       #+#    #+#	      */
/*   Updated: 2023/11/08 17:07:48 by arguez           ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlength(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	if (size > 0)
	{
		i = 0;
		while ((i < size - 1) && (src[i]))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlength(src));
}
