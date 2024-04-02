/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: arguez <marvin@42.fr>			    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/11/06 16:26:04 by arguez	       #+#    #+#	      */
/*   Updated: 2023/11/08 16:31:04 by arguez           ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1) && ptr1[i] == ptr2[i] && ptr1[i] && ptr2[i])
		i++;
	return (ptr1[i] - ptr2[i]);
}
