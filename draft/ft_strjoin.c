/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: arguez <marvin@42.fr>			    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/11/07 18:34:37 by arguez	       #+#    #+#	      */
/*   Updated: 2023/11/09 15:26:11 by arguez           ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if ((!s1) || (!s2))
		return (NULL);
	str = (char *) malloc (ft_strlength(s1) + ft_strlength(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
	{
		str[j] = s1[i];
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
