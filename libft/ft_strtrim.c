/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:16:59 by arguez            #+#    #+#             */
/*   Updated: 2023/11/13 17:06:34 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_strlength(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	checkfor_blank(const char *str, const char *set)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (!in(str[i], set))
			return (1);
		i++;
	}
	return (0);
}

static void	trimmer(const char *s1, const char *set, char *s2)
{
	int	i;
	int	j;
	int	start_flag;
	int	end_flag;

	i = 0;
	while (in(s1[i], set))
		i++;
	start_flag = i;
	while (s1[i] != '\0')
		i++;
	i--;
	while (in(s1[i], set))
		i--;
	end_flag = i;
	i = start_flag - 1;
	j = 0;
	while (++i <= end_flag)
	{
		s2[j] = s1[i];
		j++;
	}
	s2[j] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		counter;
	int		i;
	char	*s2;

	if ((!s1) || (!set))
		return (NULL);
	if (!checkfor_blank(s1, set))
		return (ft_strdup(""));
	counter = 0;
	i = 0;
	while ((in(s1[i++], set)) && (s1[i] != '\0'))
		counter++;
	while (s1[i] != '\0')
		i++;
	i--;
	while (in(s1[i--], set))
		counter++;
	s2 = (char *) malloc (ft_strlength(s1) - counter + 1);
	if (!s2)
		return (NULL);
	trimmer(s1, set, s2);
	return (s2);
}
