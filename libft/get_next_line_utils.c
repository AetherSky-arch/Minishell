/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:20:14 by arguez            #+#    #+#             */
/*   Updated: 2024/02/08 16:21:15 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lst_get_last(t_list *stash)
{
	t_list	*current;

	current = stash;
	while ((current) && (current->next))
		current = current->next;
	return (current);
}

int	found_newline(t_list *stash)
{
	t_list	*current;
	int		i;

	if (!stash)
		return (0);
	i = 0;
	current = ft_lst_get_last(stash);
	while (current->buf[i])
	{
		if (current->buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	linegen(char **line, t_list *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->buf[i])
		{
			len++;
			if (stash->buf[i] == '\n')
				break ;
			i++;
		}
		stash = stash->next;
	}
	*line = (char *)malloc(len + 1);
}

void	free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->buf);
		next = current->next;
		free(current);
		current = next;
	}
}
