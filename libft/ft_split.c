/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 23:27:44 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/29 21:54:43 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	count_words(char const *s, char c);
static size_t	len_word(char const *s, char c, size_t k);
static size_t	next_k(char const *s, char c, size_t k);
static char		**fill_split(char **split, char const *s, char c);
char			**ft_split(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	n;

	if (!s)
		return (NULL);
	n = count_words(s, c);
	split = malloc(sizeof(char *) * (n + 1));
	if (!split)
		return (NULL);
	split = fill_split(split, s, c);
	if (!split)
		return (NULL);
	split[n] = NULL;
	return (split);
}

static char	**fill_split(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	i = 0;
	while (i < count_words(s, c))
	{
		j = 0;
		k = next_k(s, c, k);
		split[i] = malloc(sizeof(char) * (len_word(s, c, k) + 1));
		if (!split[i])
		{
			while (j < i)
				free(split[j++]);
			free(split);
			return (NULL);
		}
		while (s[k] && (s[k] != c))
			split[i][j++] = s[k++];
		split[i][j] = '\0';
		k++;
		i++;
	}
	return (split);
}

static size_t	next_k(char const *s, char c, size_t k)
{
	while (s[k] && (s[k] == c))
		k++;
	return (k);
}

static size_t	len_word(char const *s, char c, size_t k)
{
	size_t	len;

	len = 0;
	while (s[k] && (s[k] == c))
		k++;
	while (s[k] && (s[k] != c))
	{
		len++;
		k++;
	}
	return (len);
}

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;
	size_t	new;

	count = 0;
	i = 0;
	new = 1;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (new == 1)
			{
				count++;
				new = 0;
			}
		}
		else
			new = 1;
		i++;
	}
	return (count);
}

/*static char	*free_split(char **split, size_t i)
{
	size_t	j;
	size_t	k;
	char	**tab;

	j = 0;
	while (j < i)
		free(split[j]);
	free(split);
	return (NULL);
}*/
/*
int	main(int argc, char **argv)
{
	tab = NULL;
	if (argc == 3)
	{
		tab = ft_split(argv[1], argv[2][0]);
		k = 0;
		while (k < count_words(argv[1], argv[2][0]))
		{
			printf("%s\n", tab[k]);
			free(tab[k]);
			k++;
		}
	}
	free(tab);
}
*/
