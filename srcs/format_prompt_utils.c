/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_prompt_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:04:21 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/03 00:08:44 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(char c)
{
	if (c == 32)
		return (1);
	if (9 <= c && c <= 13)
		return (1);
	return (0);
}

int	is_symbol(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

// 34 = " / 39 = '
int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

int	check_after_symbol(char *prompt, int i)
{
	if (prompt[i + 1] && is_symbol(prompt[i + 1]) == 1)
		return (1);
	else if (prompt[i + 1] && is_space(prompt[i + 1]) == 1)
		return (1);
	else if (prompt[i + 1])
		return (0);
	else
		return (1);
}

int	check_before_symbol(char *prompt, int i)
{
	if (i > 0 && prompt[i - 1] && is_symbol(prompt[i - 1]) == 1)
		return (1);
	else if (i > 0 && prompt[i - 1] && is_space(prompt[i - 1]) == 1)
		return (1);
	else if (i > 0 && prompt[i - 1])
		return (0);
	else
		return (1);
}
