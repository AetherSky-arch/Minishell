/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:35:55 by arguez            #+#    #+#             */
/*   Updated: 2023/11/13 17:04:54 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*ptr;

	if ((nmemb == SIZE_MAX) && (size == SIZE_MAX))
		return (NULL);
	if (size == 0)
		return (ft_strdup(""));
	if (nmemb * size > SIZE_MAX / size)
		return (NULL);
	if (nmemb * size == 0)
		return (malloc(1));
	ptr = malloc (nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size * nmemb)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
