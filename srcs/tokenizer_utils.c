/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:41:00 by aether            #+#    #+#             */
/*   Updated: 2024/04/04 15:56:46 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void char_handler(char *fprompt, int *i, int *counter)
{
	if (*i == 0)
		*counter = *counter + 1;
	else if (is_sep(fprompt[*i - 1]))
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
        else if (is_space(fprompt[i]))
			i++; // if character is a space and previous character isn't then counter++
        else if (is_sep(fprompt[i])) // (non space separators are counted as words)
        { // (assumes successive '>', '<' will be merged later)
            i++;
            counter++;
        }
        else // if previous character is separator then counter++
            char_handler(fprompt, &i, &counter);
    }
    return (counter);
}
