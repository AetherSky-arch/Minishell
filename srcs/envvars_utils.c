/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:29:26 by ae7th             #+#    #+#             */
/*   Updated: 2024/05/23 22:12:07 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_to_formats(char *formats, char f)
{
	char	*copy;
	int		i;

	if (formats == NULL)
	{
		formats = malloc(2);
		formats[0] = f;
		formats[1] = '\0';
		return (formats);
	}
	else
	{
		copy = malloc(ft_strlen(formats) + 2);
		ft_strlcpy(copy, formats, ft_strlen(formats) + 1);
		i = 0;
		while (copy[i] != '\0')
			i++;
		copy[i] = f;
		copy[i + 1] = '\0';
		free(formats);
		return (copy);
	}
}

static void	not_dollar(char *str, int *i)
{
	while ((str[*i] != '$') && (str[*i] != '\0'))
		*i = *i + 1;
}

static void	next_one_dollar(char *str, int *i)
{
	*i = *i + 1;
	while (str[*i + 1] == '$')
		*i = *i + 1;
}

char	*count_formats(char *str, char *formats)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '$')
		{
			not_dollar(str, &i);
			formats = add_to_formats(formats, 's');
		}
		else if ((str[i + 1] == '$') || (str[i + 1] == '\0'))
		{
			next_one_dollar(str, &i);
			formats = add_to_formats(formats, 's');
		}
		else
		{
			i++;
			while ((str[i] != '$') && (str[i] != '\0') && (str[i] != ' '))
				i++;
			formats = add_to_formats(formats, 'v');
		}
	}
	return (formats);
}
