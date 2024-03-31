/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:19:35 by caguillo          #+#    #+#             */
/*   Updated: 2024/03/31 23:19:03 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*format_prompt(char *prompt)
{
	char	*tmp_prompt;
	char	*f_prompt;

	if (!(prompt))
		return (NULL);
	tmp_prompt = get_prompt_minus_space(prompt);
	if (!tmp_prompt)
		return (NULL);
	f_prompt = get_prompt_plus_space(tmp_prompt);
	// printf("t %s\n", tmp_prompt);
	free(tmp_prompt);
	if (!f_prompt)
		return (NULL);
	// printf("f %s\n", f_prompt);
	// printf("p %s\n", prompt);
	return (f_prompt);
}

int	len_prompt_minus_space(char *prompt)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!prompt)
		return (0);
	while (prompt[i] && is_space(prompt[i]) == 1)
		i++;
	while (prompt[i])
	{
		if (is_quote(prompt[i]) == 1)
		{
			i++;
			len++;
			while (is_quote(prompt[i]) == 0)
			{
				i++;
				len++;
			}
		}
		if (is_space(prompt[i]) == 1)
		{
			while (prompt[i + 1] && is_space(prompt[i + 1]) == 1)
				i++;
		}
		len++;
		i++;
	}
	return (len);
}

/************** malloc to be free'd ************************/
char	*get_prompt_minus_space(char *prompt)
{
	char	*tmp_prompt;
	int		i;
	int		j;

	if (!prompt)
		return (NULL);
	tmp_prompt = malloc(sizeof(char) * (len_prompt_minus_space(prompt) + 1));
	if (!tmp_prompt)
		return (NULL);
	i = 0;
	j = 0;
	while (prompt[j] && is_space(prompt[j]) == 1)
		j++;
	while (prompt[j])
	{
		if (is_quote(prompt[j]) == 1)
		{
			tmp_prompt[i] = prompt[j];
			i++;
			j++;
			while (is_quote(prompt[j]) == 0)
			{
				tmp_prompt[i] = prompt[j];
				i++;
				j++;
			}
		}
		if (is_space(prompt[j]) == 1)
		{
			tmp_prompt[i] = ' ';
			while (prompt[j + 1] && is_space(prompt[j + 1]) == 1)
				j++;
		}
		else
			tmp_prompt[i] = prompt[j];
		i++;
		j++;
	}
	tmp_prompt[i] = '\0';
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
		if (is_quote(prompt[i]) == 1)
		{
			if (i > 0 &&  prompt[i - 1] && is_space(prompt[i - 1]) == 0)
			{
				i++;
                len++;				
			}
            i++;
			len++;
			while (is_quote(prompt[i]) == 0)
			{
				i++;
				len++;
			}
		}
		if (is_symbol(prompt[i]) == 1)
		{
			if (check_before_symbol(prompt, i) == 0)
				len++;
			if (check_after_symbol(prompt, i) == 0)
				len++;
		}
		len++;
		i++;
	}
	return (len);
}

/************** malloc to be free'd ************************/
char	*get_prompt_plus_space(char *prompt)
{
	char	*f_prompt;
	int		i;
	int		j;
	int		no_space_to_add;

	if (!prompt)
		return (NULL);
	f_prompt = malloc(sizeof(char) * (len_prompt_plus_space(prompt) + 1));
	if (!f_prompt)
		return (NULL);
	i = 0;
	j = 0;
	while (prompt[j])
	{
		if (is_quote(prompt[j]) == 1)
		{
			if (i > 0 && prompt[j - 1] && is_space(prompt[j - 1]) == 0)
			{
				f_prompt[i] = ' ';
				i++;
			}
			f_prompt[i] = prompt[j];
			i++;
			j++;
			while (is_quote(prompt[j]) == 0)
			{
				f_prompt[i] = prompt[j];
				i++;
				j++;
			}
		}
		if (is_symbol(prompt[j]) == 1)
		{
			no_space_to_add = 1;
			if (check_before_symbol(prompt, j) == 0)
			{
				f_prompt[i] = ' ';
				i++;
				f_prompt[i] = prompt[j];
				no_space_to_add = 0;
			}
			if (check_after_symbol(prompt, j) == 0)
			{
				if (no_space_to_add == 1)
					f_prompt[i] = prompt[j];
				i++;
				f_prompt[i] = ' ';
				no_space_to_add = 0;
			}
			if (no_space_to_add == 1)
				f_prompt[i] = prompt[j];
		}
		else
			f_prompt[i] = prompt[j];
		j++;
		i++;
	}
	f_prompt[i] = '\0';
	return (f_prompt);
}
