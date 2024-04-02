/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:17:35 by arguez            #+#    #+#             */
/*   Updated: 2023/11/13 16:37:07 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	*res;
	int		i;

	res = NULL;
	ptr = (char *)s;
	i = 0;
	while (ptr[i] != '\0')
	{
		if ((unsigned char)c == ptr[i])
			res = &ptr[i];
		i++;
	}
	if ((unsigned char)c == ptr[i])
		res = &ptr[i];
	return (res);
}
