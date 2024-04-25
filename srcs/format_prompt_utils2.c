/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_prompt_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:58:52 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/24 22:41:23 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quote_in_len_minus(char *prompt, int *i, int *len, int q)
{
	if (prompt[*i + 1])
	{
		(*i)++;
		(*len)++;
	}
	while (prompt[*i] && prompt[*i] != q)
	{
		(*i)++;
		(*len)++;
	}
}

void	space_in_len_minus(char *prompt, int *i)
{
	while (prompt[*i] && is_space(prompt[*i]) == 1)
		(*i)++;
	if (prompt[*i])
		(*i)--;
}

void	squote_in_get_minus(char *tmp_prompt, char *prompt, int *i, int *j)
{
	tmp_prompt[*i] = prompt[*j];
	(*i)++;
	(*j)++;
	while (prompt[*j] && prompt[*j] != '\'')
	{
		tmp_prompt[*i] = prompt[*j];
		(*i)++;
		(*j)++;
	}
}

void	dquote_in_get_minus(char *tmp_prompt, char *prompt, int *i, int *j)
{
	tmp_prompt[*i] = prompt[*j];
	(*i)++;
	(*j)++;
	while (prompt[*j] && prompt[*j] != '\"')
	{
		tmp_prompt[*i] = prompt[*j];
		(*i)++;
		(*j)++;
	}
}

void	space_in_get_minus(char *prompt, int *j)
{
	while (prompt[*j] && is_space(prompt[*j]) == 1)
		(*j)++;
	if (prompt[*j])
		(*j)--;
}
