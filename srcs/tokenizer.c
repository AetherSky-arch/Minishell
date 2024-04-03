/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:26:27 by aether            #+#    #+#             */
/*   Updated: 2024/04/03 20:47:28 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void  tokenizer(t_mini *mini)
{
    int i;
    int j;

    j = 0;
    i = 1;
    token_init(mini->token, mini->fprompt);
    while (mini->fprompt[i] != '\0')
    {
        if ((is_sep(mini->fprompt[i])) && (is_in_quotes(mini->fprompt, i) == 0))


    }
}
