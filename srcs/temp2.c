/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 21:19:45 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/09 21:38:43 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	is_in_quotes(char *prompt, int i)
{
	int		j;
	int		open_quote;
	char	q;

	q = prompt[i];
	j = 0;
	open_quote = 0;
	while (j <= i)
	{
		if ((prompt[j] == q) && (open_quote == 0))
			open_quote = 1;
		else if ((prompt[j] == q) && (open_quote == 1))
			open_quote = 0;
		j++;
	}
	return (open_quote);
}

// 0 = false, not inside quotes - 1 = true, inside quotes
// opening quote not included (0), closing quote not included (0)
int	is_in_quotes2(char *str, int i)
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
	// if (str[i] == '\'' || str[i] == '\"')
	// 	return (1); // true, in quote --> to include last quote
	if (first == 0)
		return (0); // false, not in quote
	// if ((first == 39) && (s_open % 2 == 0))
	// 	return (0); // ??
	// if ((first == 34) && (d_open % 2 == 0))
	// 	return (0); // ??
	if ((first == 39) && (str[i] == '\''))
		return (0); //not include the first
	if ((first == 34) && (str[i] == '\"'))
		return (0); //not include the first
	return (1); // true, in quote
}

int	main(int argc, char **argv)
{
	int		i;
	char	*str;

	(void)argc;
	(void)argv;
	// str = "titi \" \' toto\" tutu";
	str = "titi \" \' tot\'o\" tutu \'tat\"a\'   \"tst\'s\"";
	// str = "echo \'t\"o\'t\"\"o";
	// str = " \' "; // stx err
	// str = "titi \"  toto\" tutu";
	// str = "titi \' \" toto\' tutu";
	// str = "titi \' \" tot\'o\" tutu"; //stx err
	// str = "titi \'  toto\' tutu";
	// str = "titi \' \" tot\"o\' tutu";
	// str = "\' \" tot\"o\' tutu";
	// str = "\' \" tot\"o\'";
	i = 0;
	while (str[i])
	{
		// printf("%d - %c = %d\n", i, str[i], is_in_quotes(str, i));
		printf("%d - %c = %d\n", i, str[i], is_in_quotes2(str, i));
		i++;
	}
}
