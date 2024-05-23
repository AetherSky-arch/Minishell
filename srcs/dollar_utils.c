/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:28:02 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/23 22:30:23 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	idx_dollar(char *str, int start)
{
	size_t	i;

	if (!str)
		return (-1);
	i = start;
	if (i >= ft_strlen(str))
		return (-1);
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == 0)
				return (-1);
			if (is_space(str[i + 1]) == 1)
				return (-1);
			if (is_quote(str[i + 1]) == 1)
				return (-1);
			if (str[i + 1] == '=')
				return (-1);
			if (str[i + 1] != '$')
				return (i);
		}
		i++;
	}
	return (-1);
}

int	end_dollar(char *str, int start)
{
	int	k;
	int	idx;

	if (!str)
		return (0);
	idx = idx_dollar(str, start);
	k = idx + 1;
	while (str[k])
	{
		if ((str[k] == '?' || ft_isdigit(str[k]) == 1) && k == idx + 1)
		{
			k++;
			break ;
		}
		if (str[k] == '$' || str[k] == '=' || is_space(str[k]) == 1
			|| is_quote(str[k]) == 1 || str[k] == '/')
			break ;
		k++;
	}
	return (k - 1);
}

int	is_loop(char *varname, char *varvalue)
{
	char	*tmp;

	tmp = ft_strjoin("$", varname);
	if (ft_strcmp(tmp, varvalue) == 0)
		return (free(tmp), 1);
	return (free(tmp), 0);
}

char	*get_before(char *tok, int start)
{
	int		i;
	char	*before;

	if (!tok)
		return (NULL);
	i = idx_dollar(tok, start);
	if (i > 0)
		before = gnl_substr(tok, 0, i);
	else
		before = ft_strdup("");
	return (before);
}

char	*get_after(char *tok, int start)
{
	int		k;
	char	*after;

	if (!tok)
		return (NULL);
	k = end_dollar(tok, start);
	if ((unsigned int)k < ft_strlen(tok) - 1)
		after = gnl_substr(tok, k + 1, ft_strlen(tok));
	else
		after = ft_strdup("");
	return (after);
}
