/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:49:18 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/25 02:19:43 by caguillo         ###   ########.fr       */
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
	int i;
	char *tmp;

	if (!type || !token)
		return ;
	i = 0;
	while (i < ft_tabstr_len(token))
	{
		if (type[i] == INFILE || type[i] == OUTFILE || type[i] == OUTFAPP
			|| type[i] == LIMITER || type[i] == CMD || type[i] == ARG)
		{
			if (is_quote(token[i][0]) == 1)
			{
				tmp = ft_strdup(token[i]);
				free(token[i]);
				token[i] = gnl_substr(tmp, 1, ft_strlen(tmp) - 2);
				free(tmp);
			}
		}
		i++;
	}
}
