/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:07:30 by aether            #+#    #+#             */
/*   Updated: 2024/04/08 23:46:46 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int  check_for_unclosed_quotes(char *prompt)
{
    int i;
    int singles;
    int doubles;

    i = 0;
    singles = 0;
    doubles = 0;
    while (prompt[i] != '\0')
    {
        if (prompt[i] == 34)
            doubles++;
        if (prompt[i] == 39)
            singles++;
        i++;
    }
    if ((singles % 2 != 0) || (doubles % 2 != 0))
        return (0);
    return (1);
}

static int  count_less_more(char *prompt, int *i)
{
    char  original;
    int   res;

    original = prompt[*i];
    res = 1;
    while (get_next_char(prompt, *i) == original)
    {
        *i = *i + 1;
        res++;
    }
    if (res > 2)
        return (0);
    return (1);
}

static int  check_less_more(char *prompt)
{
    int i;

    i = 0;
    while (prompt[i] != '\0')
    {
        if ((prompt[i] == '>') || (prompt[i] == '<'))
        {
            if (count_less_more(prompt, &i) == 0)
                return (0);
        }
        i++;
    }
    return (1);
}

int syntax_checker(char *prompt)
{
    if (check_for_unclosed_quotes(prompt) == 0)
    //     return (0);
    if (check_less_more(prompt) == 0)
        return (0);
    if (check_pipes(prompt) == 0)
        return (0);
    return (1);
}
