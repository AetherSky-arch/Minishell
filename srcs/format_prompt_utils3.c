/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_prompt_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:33:29 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/09 19:37:58 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	other_in_get_minus(char *tmp_prompt, char *prompt, int *i, int *j)
{
	if (prompt[*j] && (is_space(prompt[*j]) == 1))
		tmp_prompt[*i] = 32;
	else
		tmp_prompt[*i] = prompt[*j];
	(*i)++;
	(*j)++;
}

void	quote_in_len_plus(char *prompt, int *i, int *len, int q)
{
	// if (*i > 0 && prompt[*i - 1] && (is_space(prompt[*i - 1]) == 0))
	// 	(*len)++;
	if (prompt[*i + 1])
	{
		(*i)++;
		(*len)++;
	}
	while (prompt[*i] && (prompt[*i] != q))
	{
		(*i)++;
		(*len)++;
	}
	if (prompt[*i])
	{
		(*i)++;
		(*len)++;
	}
	// if (prompt[*i] && (is_space(prompt[*i]) == 0))
	// 	(*len)++;
}

void	symbol_in_len_plus(char *prompt, int *i, int *len)
{
	if (check_before_symbol(prompt, *i) == 0)
		(*len)++;
	if (check_after_symbol(prompt, *i) == 0)
		(*len)++;
	(*i)++;
	(*len)++;
}

void	squote_in_get_plus(char *f_prompt, char *prompt, int *i, int *j)
{
	// if (*j > 0 && prompt[*j - 1] && (is_space(prompt[*j - 1]) == 0))
	// {
	// 	f_prompt[*i] = ' ';
	// 	(*i)++;
	// }
	if (prompt[*j])
	{
		f_prompt[*i] = prompt[*j];
		(*i)++;
		(*j)++;
	}
	while (prompt[*j] && (prompt[*j] != '\''))
	{
		f_prompt[*i] = prompt[*j];
		(*i)++;
		(*j)++;
	}
	squote_in_get_plus2(f_prompt, prompt, i, j);
}

void	squote_in_get_plus2(char *f_prompt, char *prompt, int *i, int *j)
{
	if (prompt[*j])
	{
		f_prompt[*i] = prompt[*j];
		(*j)++;
		(*i)++;
	}
	// if (prompt[*j] && (is_space(prompt[*j]) == 0))
	// {
	// 	f_prompt[*i] = ' ';
	// 	(*i)++;
	// }
}
