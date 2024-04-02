/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: arguez <marvin@42.fr>			    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/11/07 11:36:00 by arguez	       #+#    #+#	      */
/*   Updated: 2023/11/08 17:20:50 by arguez           ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlength(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	little_len;
	char	*hay;

	if ((!big) && (len == 0))
		return (0);
	i = 0;
	hay = (char *)big;
	little_len = ft_strlength(little);
	if (little_len == 0 || big == little)
		return (hay);
	while (hay[i] != '\0' && i < len)
	{
		c = 0;
		while (hay[i + c] != '\0' && little[c] != '\0'
			&& hay[i + c] == little[c] && i + c < len)
			c++;
		if (c == little_len)
			return (hay + i);
		i++;
	}
	return (0);
}
