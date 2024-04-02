/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:17:35 by arguez            #+#    #+#             */
/*   Updated: 2023/11/13 16:36:38 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	ptr = (char *)s;
	i = 0;
	while (ptr[i] != '\0')
	{
		if ((unsigned char)c == ptr[i])
			return (&ptr[i]);
		i++;
	}
	if ((unsigned char)c == ptr[i])
		return (&ptr[i]);
	return (NULL);
}
