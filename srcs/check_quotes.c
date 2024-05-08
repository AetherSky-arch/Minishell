/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:49:18 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/09 01:33:22 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// 34 = " / 39 = '
int	check_quotes(char *str)
{
	int	i;
	int	d_open;
	int	s_open;

	d_open = 0;
	s_open = 0;
	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == 39 && d_open == 0 && s_open == 0)
			s_open = 1;
		else if (str[i] == 39 && d_open == 0 && s_open == 1)
			s_open = 0;
		else if (str[i] == 34 && s_open == 0 && d_open == 0)
			d_open = 1;
		else if (str[i] == 34 && s_open == 0 && d_open == 1)
			d_open = 0;
		i++;
	}
	return (check_quotes_output(s_open, d_open));
}

int	check_quotes_output(int s_open, int d_open)
{
	if (s_open == 1)
	{
		ft_putstr_fd(ERR_SQX, STD_ERR);
		return (EXIT_STX);
	}
	if (d_open == 1)
	{
		ft_putstr_fd(ERR_DQX, STD_ERR);
		return (EXIT_STX);
	}
	return (0);
}

void	check_quoted_type(t_type *type, char **token)
{
	int		i;
	char	*tmp;
	int		j;

	if (!type || !token)
		return ;
	i = 0;
	while (i < ft_tabstr_len(token))
	{
		if (type[i] == INFILE || type[i] == OUTFILE || type[i] == OUTFAPP
			|| type[i] == LIMITER || type[i] == CMD || type[i] == ARG)
		{
			j = 0;
			while (token[i][j])
			{
				if (is_quote(token[i][j]) == 1)
				{
					tmp = remove_quote(token[i]);
					free(token[i]);
					token[i] = ft_strdup(tmp);
					free(tmp);
					break ;
				}
				j++;
			}
			// if (is_quote(token[i][0]) == 1)
			// {
			// 	tmp = ft_strdup(token[i]);
			// 	free(token[i]);
			// 	token[i] = gnl_substr(tmp, 1, ft_strlen(tmp) - 2);
			// 	free(tmp);
			// }
		}
		i++;
	}
}

char	*remove_quote(char *str)
{
	int		i;
	char	q;
	char	*new;
	int		k;
	int		j;

	if (!str)
		return (NULL);
	k = 0;
	i = 0;
	while (str[i])
	{
		if ((is_quote(str[i]) == 1) && (k == 0))
			q = str[i];
		if (str[i] == q)
			k++;
		i++;
	}
	new = malloc(sizeof(char) * (ft_strlen(str) - k + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != q)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[i] = '\0';
	return (new);
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
