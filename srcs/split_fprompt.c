/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_fprompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 23:27:44 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/29 01:01:37 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		inside_quotes(char *str, int i);
static size_t	count_words(char const *s, char c);
static size_t	len_word(char const *s, char c, size_t k);
static size_t	next_k(char const *s, char c, size_t k);
static char		**fill_split(char **split, const char *s, char c);
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

static char	**fill_split(char **split, const char *s, char c)
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

// modified
static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;
	size_t	new;
	int		open;

	count = 0;
	i = 0;
	new = 1;
	while (s[i])
	{
		if (inside_quote(s[i]) == 1)
			if (s[i] != c || (s[i] == c && inside_quotes(s, i) == 1))
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

static int	inside_quotes(char *str, int i)
{
	int	j;
	int	s_open;
	int	d_open;
	int	first;

	if (!str)
		return (0);
	j = 0;
	s_open = 0;
	d_open = 0;
	first = 0;
	while (j <= i)
	{
		if (str[j] == '\'')
		{
			if (first == 0)
				first = 39;
			s_open++;
			if (first == 39 && s_open % 2 == 0)
			{
				first = 0;
				d_open = 0;
			}
		}
		if (str[j] == '\"')
		{
			if (first == 0)
				first = 34;
			d_open++;
			if (first == 34 && d_open % 2 == 0)
			{
				first = 0;
				s_open = 0;
			}
		}
		j++;
	}
	if (first == 0)
		return (0); // false, not in quote
	if ((first == 39) && (s_open % 2 == 0))
		return (0);
	if ((first == 34) && (d_open % 2 == 0))
		return (0);
	return (1); // true, in quote
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
