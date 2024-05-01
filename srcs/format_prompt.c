/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:19:35 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/01 22:58:01 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*format_prompt(char *prompt)
{
	char	*tmp_prompt;
	char	*f_prompt;

	if (!prompt)
		return (NULL);	
	tmp_prompt = get_prompt_minus_space(prompt);
	if (!tmp_prompt)
		return (NULL);
	f_prompt = get_prompt_plus_space(tmp_prompt);
	free(tmp_prompt);
	if (!f_prompt)
		return (NULL);
	return (f_prompt);
}

int	len_prompt_minus_space(char *prompt)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (prompt[i] && is_space(prompt[i]) == 1)
		i++;
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '\"')
			quote_in_len_minus(prompt, &i, &len, prompt[i]);
		if (is_space(prompt[i]) == 1)
			space_in_len_minus(prompt, &i);
		if (prompt[i])
		{
			len++;
			i++;
		}
	}
	// printf("len-=%d\n", len);
	return (len);
}

/************** malloc to be free'd ************************/
char	*get_prompt_minus_space(char *prompt)
{
	char	*tmp_prompt;
	int		i;
	int		j;

	tmp_prompt = malloc(sizeof(char) * (len_prompt_minus_space(prompt) + 1));
	if (!tmp_prompt)
		return (NULL);
	i = 0;
	j = 0;
	while (prompt[j] && is_space(prompt[j]) == 1)
		j++;
	while (prompt[j])
	{
		if (prompt[j] == '\'')
			squote_in_get_minus(tmp_prompt, prompt, &i, &j);
		if (prompt[j] == '\"')
			dquote_in_get_minus(tmp_prompt, prompt, &i, &j);
		if (is_space(prompt[j]) == 1)
			space_in_get_minus(prompt, &j);
		if (prompt[j])
			other_in_get_minus(tmp_prompt, prompt, &i, &j);
	}
	tmp_prompt[i] = '\0';
	// printf("strlen-=%d\n", (int)ft_strlen(tmp_prompt));
	return (tmp_prompt);
}

int	len_prompt_plus_space(char *prompt)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!prompt)
		return (0);
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '\"')
			quote_in_len_plus(prompt, &i, &len, prompt[i]);
		else if (is_symbol(prompt[i]) == 1)
			symbol_in_len_plus(prompt, &i, &len);
		else
		{
			i++;
			len++;
		}
	}
	// printf("len+=%d\n", len);
	return (len);
}

/************** malloc to be free'd ************************/
char	*get_prompt_plus_space(char *prompt)
{
	char	*f_prompt;
	int		i;
	int		j;

	if (!prompt)
		return (NULL);
	f_prompt = malloc(sizeof(char) * (len_prompt_plus_space(prompt) + 1));
	if (!f_prompt)
		return (NULL);
	i = 0;
	j = 0;
	while (prompt[j])
	{
		if (prompt[j] == '\'')
			squote_in_get_plus(f_prompt, prompt, &i, &j);
		else if (prompt[j] == '\"')
			dquote_in_get_plus(f_prompt, prompt, &i, &j);
		else if (is_symbol(prompt[j]) == 1)
			symbol_in_get_plus(f_prompt, prompt, &i, &j);
		else
			other_in_get_plus(f_prompt, prompt, &i, &j);
	}
	f_prompt[i] = '\0';
	// printf("strlen+=%d\n", (int)ft_strlen(f_prompt));
	return (f_prompt);
}
