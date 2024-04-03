/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:41:00 by aether            #+#    #+#             */
/*   Updated: 2024/04/03 21:12:30 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void space_handler(char *fprompt, int *i, int *counter)
{
    if (*i > 0) // prevents segfault by attempting to access index -1 of fprompt
    {
        if (is_space(fprompt[*i - 1]) == 0)
            *counter = *counter + 1;
    }
    *i = *i + 1;
}

static void char_handler(char *fprompt, int *i, int *counter)
{
    if (is_sep(fprompt[*i - 1]))
        *counter = *counter + 1;
    *i = *i + 1;
}

static void quotes_handler(char *fprompt, int *i, int *counter)
{
    while ((is_in_quotes(fprompt, *i)) && (fprompt[*i] != '\0'))
        *i = *i + 1;
    *i = *i + 1;
    *counter = *counter + 1;
}

int  blocks_counter(char *fprompt)
{
    int i;
    int counter;

    i = 0;
    counter = 0;
    while (fprompt[i] != '\0')
    {
        if (is_quote(fprompt[i])) // /!\ doesn't work with intertwined single and double quotes
            quotes_handler(fprompt, &i, &counter); // if found quote, go to end of quote then counter++
        else if (is_space(fprompt[i])) // if character is a space and previous character isn't then counter++
            space_handler(fprompt, &i, &counter);
        else if (is_sep(fprompt[i])) // (non space separators are counted as words)
        { // (assumes successive '>', '<' will be merged later)
            i++;
            counter++;
        }
        else if (i > 0) // if previous character is separator then counter++
            char_handler(fprompt, &i, &counter);
        else
            i++;
    }
    return (counter);
}

int main(void)
{
    ft_printf("%d\n", blocks_counter("hel|lo \"th|is is \" a sen>tence. "));
}
