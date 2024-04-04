/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:00:24 by aether            #+#    #+#             */
/*   Updated: 2024/04/04 15:54:36 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int  is_sep(char c)
{
    if ((is_space(c)) || (is_symbol(c)) || (is_quote(c)))
        return (1);
    return (0);
}

int  is_in_quotes(char *prompt, int i)
{
    int j;
    int open_quote;

    j = 0;
    open_quote = 0;
    while (j <= i)
    {
        if ((is_quote(prompt[j])) && (open_quote == 0))
            open_quote = 1;
		else if ((is_quote(prompt[j])) && (open_quote == 1))
            open_quote = 0;
        j++;
    }
    return (open_quote);
}
