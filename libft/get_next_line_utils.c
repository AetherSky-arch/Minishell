/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:18:25 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/08 20:51:29 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// "" + s2 = s2 ok, mais NULL + s2 = ? donc NULL
char	*gnl_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (free(s1), NULL);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (free(s1), NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (free(s1), join);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

// because a char is 1 byte = 1 octet (= 8 bits)
// on each octet, we set 0, (not only on each element)
void	*ft_calloc(size_t nb_elem, size_t size_in_oct)
{
	void	*str;
	size_t	i;

	if (size_in_oct != 0 && (nb_elem > (size_t)(-1) / size_in_oct))
		return (NULL);
	str = malloc(nb_elem * size_in_oct);
	if (!str)
		return (NULL);
	i = 0;
	while (i < nb_elem * size_in_oct)
	{
		((unsigned char *)str)[i] = 0;
		i++;
	}
	return (str);
}

// size_t = portable (32/64) unsigned int, so same or bigger
// start = indice, length = longueur
// lenght = 0 => ""
// start = n => NULL
char	*gnl_substr(char *str, unsigned int start, size_t lenght)
{
	char			*sub;
	unsigned int	i;
	size_t			size;

	if (!str)
		return (NULL);
	if (start >= ft_strlen(str))
		size = 0;
	else if (start + lenght - 1 >= ft_strlen(str))
		size = ft_strlen(str) - start;
	else
		size = lenght;
	sub = malloc(sizeof(char) * (size + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < size && str[i + start])
	{
		sub[i] = str[i + start];
		i++;
	}
	sub[size] = '\0';
	return (sub);
}

ssize_t	is_nl(char *str)
{
	size_t	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
