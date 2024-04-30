/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_prompt_utils4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:04:59 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/30 03:01:34 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dquote_in_get_plus(char *f_prompt, char *prompt, int *i, int *j)
{
	if (*j > 0 && prompt[*j - 1] && (is_space(prompt[*j - 1]) == 0))
	{
		f_prompt[*i] = ' ';
		(*i)++;
	}
	if (prompt[*j])
	{
		f_prompt[*i] = prompt[*j];
		(*i)++;
		(*j)++;
	}
	while (prompt[*j] && (prompt[*j] != '\"'))
	{
		f_prompt[*i] = prompt[*j];
		(*i)++;
		(*j)++;
	}
	dquote_in_get_plus2(f_prompt, prompt, i, j);
}

void	dquote_in_get_plus2(char *f_prompt, char *prompt, int *i, int *j)
{
	if (prompt[*j])
	{
		f_prompt[*i] = prompt[*j];
		(*j)++;
		(*i)++;
	}
	if (prompt[*j] && (is_space(prompt[*j]) == 0))
	{
		f_prompt[*i] = ' ';
		(*i)++;
	}
}

void	symbol_in_get_plus(char *f_prompt, char *prompt, int *i, int *j)
{
	int	no_space_to_add;

	no_space_to_add = 1;
	if (check_before_symbol(prompt, *j) == 0)
	{
		f_prompt[*i] = ' ';
		(*i)++;
		f_prompt[*i] = prompt[*j];
		no_space_to_add = 0;
	}
	if (check_after_symbol(prompt, *j) == 0)
	{
		if (no_space_to_add == 1)
			f_prompt[*i] = prompt[*j];
		(*i)++;
		f_prompt[*i] = ' ';
		no_space_to_add = 0;
	}
	if (no_space_to_add == 1)
		f_prompt[*i] = prompt[*j];
	(*i)++;
	(*j)++;
}

void	other_in_get_plus(char *f_prompt, char *prompt, int *i, int *j)
{
	f_prompt[*i] = prompt[*j];
	(*j)++;
	(*i)++;
}
