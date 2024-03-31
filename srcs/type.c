/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:58:45 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/01 00:21:18 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/****************malloc to be free'd***********/
t_type	*create_type(char **token)
{
	t_type	*type;
	int		i;

	if (!token)
		return (NULL);
	type = malloc(sizeof(t_type) * ft_tablen(token));
	if (!type)
		return (NULL);
	i = 0;
	while (token[i])
	{
		type[i] = get_type(token, i);
		i++;
	}
	return (type);
}

t_type	get_type(char **token, int i)
{
	if (ft_strcmp(token[i], "<") == 0)
		return (LESS);
	else if (ft_strcmp(token[i], "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(token[i], ">") == 0)
		return (GREAT);
	else if (ft_strcmp(token[i], ">>") == 0)
		return (DGREAT);
	else if (ft_strcmp(token[i], "|") == 0)
		return (PIPE);
	else if (i > 0 && token[i - 1] && ft_strcmp(token[i - 1], "<") == 0)
		return (INFILE);
	else if (i > 0 && token[i - 1] && ft_strcmp(token[i - 1], "<<") == 0)
		return (LIMITER);
	else if (i > 0 && token[i - 1] && ft_strcmp(token[i - 1], ">") == 0)
		return (OUTFILE);
	else if (i > 0 && token[i - 1] && ft_strcmp(token[i - 1], ">>") == 0)
		return (OUTFAPP);
	else if (i > 0 && token[i - 1] && ft_strcmp(token[i - 1], "|") == 0)
		return (CMD);
	else
		return (get_type2(token, i));
}

t_type	get_type2(char **token, int i)
{
	if (i == 0)
		return (CMD);
	else if (token[i + 1] && ft_strcmp(token[i + 1], "|") == 0)
	{
		if (access(token[i], X_OK) == 0)
			return (CMD);
		else
			return (ARG);
	}
	else
		return (ARG);
}

size_t	ft_tablen(char **tab)
{
	size_t	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}
