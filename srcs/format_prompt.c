/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:19:35 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/04 03:57:34 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*format_prompt(char *prompt)
{
	char	*tmp_prompt;
	char	*f_prompt;

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
	while (prompt[i] && is_space(prompt[i]) == 1)
		i++;
	while (prompt[i])
	{
		if (prompt[i] == 39)
		{
			i++;
			len++;
			while (prompt[i] != 39)
			{
				i++;
				len++;
			}
		}
		if (prompt[i] && is_space(prompt[i]) == 1)
		{
			while (prompt[i] && is_space(prompt[i]) == 1)
				i++;
			if (prompt[i])
				i--;
		}
		if (prompt[i])
		{
			len++;
			i++;
		}
	}
	printf("len-=%d\n", len);
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
		if (prompt[j] == 39)
		{
			tmp_prompt[i] = prompt[j];
			i++;
			j++;
			while (prompt[j] != 39)
			{
				tmp_prompt[i] = prompt[j];
				i++;
				j++;
			}
		}
		if (prompt[j] && is_space(prompt[j]) == 1)
		{
			while (prompt[j] && is_space(prompt[j]) == 1)
				j++;
			if (prompt[j])
				j--;
		}
		if (prompt[j])
		{
			tmp_prompt[i] = prompt[j];
			i++;
			j++;
		}
	}
	tmp_prompt[i] = '\0';
	printf("strlen-=%d\n", (int)ft_strlen(tmp_prompt));
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
		if (prompt[i] == 39)
		{
			if (i > 0 && prompt[i - 1] && is_space(prompt[i - 1]) == 0)
				len++;
			i++;
			len++;
			while (prompt[i] != 39)
			{
				i++;
				len++;
			}
			i++;
			len++;
			if (prompt[i] && is_space(prompt[i]) == 0)
				len++;
		}
		if (is_symbol(prompt[i]) == 1)
		{
			if (check_before_symbol(prompt, i) == 0)
				len++;
			if (check_after_symbol(prompt, i) == 0)
				len++;
		}
		if (prompt[i])
		{
			i++;
			len++;
		}
	}
	printf("len+=%d\n", len);
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
		//
		if (prompt[j] == 39)
		{
			if (j > 0 && prompt[j - 1] && is_space(prompt[j - 1]) == 0)
			{
				f_prompt[i] = ' ';
				i++;
			}
			f_prompt[i] = prompt[j];
			i++;
			j++;
			while (prompt[j] != 39)
			{
				f_prompt[i] = prompt[j];
				i++;
				j++;
			}
			f_prompt[i] = prompt[j];
			j++;
			i++;
			if (prompt[j] && is_space(prompt[j]) == 0)
			{
				f_prompt[i] = ' ';
				i++;
			}
		}
		//
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
		//
		if (prompt[j])
		{
			f_prompt[i] = prompt[j];
			j++;
			i++;
		}
	}
	f_prompt[i] = '\0';
	printf("strlen+=%d\n", (int)ft_strlen(f_prompt));
	return (f_prompt);
}
