/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: arguez <marvin@42.fr>			    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/11/06 16:05:41 by arguez	       #+#    #+#	      */
/*   Updated: 2023/11/13 16:38:02 by arguez           ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static size_t	ft_strlength(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	size_t			total_length;

	if (size == 0)
		return (ft_strlength(src));
	total_length = ft_strlength(src) + ft_strlength(dst);
	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	if (i == size)
		return (i + ft_strlength(src));
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (total_length);
}
