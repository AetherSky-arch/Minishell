/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:26:53 by aether            #+#    #+#             */
/*   Updated: 2024/04/08 18:57:59 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char get_next_char(char *prompt, int i)
{
    i++;
    while ((prompt[i] == ' ') && (prompt[i] != '\0'))
        i++;
    return (prompt[i]);
}

int check_pipes(char *prompt)
{
    int i;

    i = 0;
    while (prompt[i] != '\0')
    {
        if (prompt[i] == '|')
        {
            if (get_next_char(prompt, i) == '|')
                return (0);
        }
        i++;
    }
    return (1);
}
