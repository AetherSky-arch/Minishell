/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:26:27 by aether            #+#    #+#             */
/*   Updated: 2024/04/09 17:01:08 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	space_handler(int *i, int *j)
{
	*i = *i + 1;
	*j = *j + 1;
}

static void	sep_handler(char **token, char sep, int *i, int *j)
{
	char	*elem;
	int		n;

	n = 0;
	while (token[n] != NULL)
		n++;
	elem = malloc(2);
	if (elem == NULL)
		return ;
	elem[0] = sep;
	elem[1] = '\0';
	token[n] = elem;
	*i = *i + 1;
	*j = *j + 1;
	token[n + 1] = NULL;
}

static void	quotes_handler(char **token, char *fprompt, int *i, int *j)
{
	int	n;

	while (is_in_quotes(fprompt, *i))
		*i = *i + 1;
	n = 0;
	while (token[n] != NULL)
		n++;
	token[n] = ft_substr(fprompt, *j, *i - *j);
	token[n + 1] = NULL;
	*j = *i;
}

static void	char_handler(char **token, char *fprompt, int *i, int *j)
{
	int	n;

	while ((is_space(fprompt[*i]) == 0) && (fprompt[*i] != '\0'))
		*i = *i + 1;
	n = 0;
	while (token[n] != NULL)
		n++;
	token[n] = ft_substr(fprompt, *j, *i - *j);
	token[n + 1] = NULL;
	*j = *i;
}

void  tokenizer(t_mini *mini)
{
    int i;
    int j;

    j = 0;
    i = 0;
    mini->token = token_init(mini->token, mini->fprompt);
	if (mini->token == NULL)
		return ;
	mini->token[0] = NULL;
    while (mini->fprompt[i] != '\0')
    {
		if (is_quote(mini->fprompt[i]))
			quotes_handler(mini->token, mini->fprompt, &i, &j);
		else if (is_space(mini->fprompt[i]))
			space_handler(&i, &j);
		else if (is_sep(mini->fprompt[i]))
			sep_handler(mini->token, mini->fprompt[i], &i, &j);
		else
			char_handler(mini->token, mini->fprompt, &i, &j);
    }
}
