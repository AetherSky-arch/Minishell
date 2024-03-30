/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_prompt_tools1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:04:21 by caguillo          #+#    #+#             */
/*   Updated: 2024/03/30 21:41:14 by caguillo         ###   ########.fr       */
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
	if (prompt[i - 1] && is_symbol(prompt[i - 1]) == 1)
		return (1);
	else if (prompt[i - 1] && is_space(prompt[i - 1]) == 1)
		return (1);
	else if (prompt[i - 1])
		return (0);
	else
		return (1);
}
