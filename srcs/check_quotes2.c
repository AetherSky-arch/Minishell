/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 02:42:00 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/24 02:42:23 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	squote_check(int *first, int *s_open, int *d_open)
{
	if (*first == 0)
		*first = 39;
	*s_open = *s_open + 1;
	if (*first == 39 && *s_open % 2 == 0)
	{
		*first = 0;
		*d_open = 0;
	}
}

static void	dquote_check(int *first, int *s_open, int *d_open)
{
	if (*first == 0)
		*first = 34;
	*d_open = *d_open + 1;
	if (*first == 34 && *d_open % 2 == 0)
	{
		*first = 0;
		*s_open = 0;
	}
}

int	inside_quotes(const char *str, int i)
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
			squote_check(&first, &s_open, &d_open);
		if (str[j] == '\"')
			dquote_check(&first, &s_open, &d_open);
		j++;
	}
	if ((first == 39) && (str[i] == '\''))
		return (0);
	if ((first == 34) && (str[i] == '\"'))
		return (0);
	return (first);
}

/*** draft ***/
// if (first == 0)
// 	return (0);
