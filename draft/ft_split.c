/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: arguez <marvin@42.fr>			    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/11/08 12:04:50 by arguez	       #+#    #+#	      */
/*   Updated: 2024/03/07 17:31:59 by arguez           ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	if (str[i] == '\0')
		return (counter);
	if (str[i] != c)
		counter++;
	i++;
	while (str[i] != '\0')
	{
		if ((str[i] != c) && (str[i - 1] == c))
			counter++;
		i++;
	}
	return (counter);
}

static int	goto_nextword(const char *str, int j, char c)
{
	while (str[j] == c)
		j++;
	return (j);
}

static char	*getword(char const *str, int *j, char c)
{
	int		i;
	int		k;
	char	*word;

	i = *j - 1;
	while ((str[*j] != c) && (str[*j] != '\0'))
		*j = *j + 1;
	*j = *j - 1;
	word = (char *) malloc ((*j - i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	k = 0;
	while (i++ != *j)
	{
		word[k] = str[i];
		k++;
	}
	word[k] = '\0';
	*j = *j + 1;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		numof_words;
	int		i;
	int		j;
	char	**strs;

	if (!s)
		return (NULL);
	numof_words = count_words(s, c);
	strs = (char **) malloc ((numof_words + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (i < numof_words)
	{
		j = goto_nextword(s, j, c);
		strs[i] = getword(s, &j, c);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
