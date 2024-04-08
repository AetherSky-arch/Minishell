/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:39:48 by arguez            #+#    #+#             */
/*   Updated: 2024/02/08 14:26:14 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	add_to_stash(t_list **stash, char *buffer, int readd)
{
	t_list	*last;
	t_list	*new_node;
	int		i;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->buf = (char *)malloc(readd + 1);
	if (!new_node->buf)
		return ;
	i = 0;
	while ((buffer[i]) && (i < readd))
	{
		new_node->buf[i] = buffer[i];
		i++;
	}
	new_node->buf[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lst_get_last(*stash);
	last->next = new_node;
}

void	read_and_stash(int fd, t_list **stash, int *readd)
{
	char	*buffer;

	while ((!found_newline(*stash)) && (*readd != 0))
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		*readd = read(fd, buffer, BUFFER_SIZE);
		if (((*readd == 0) && (*stash == NULL)) || (*readd == -1))
		{
			free(buffer);
			return ;
		}
		buffer[*readd] = '\0';
		add_to_stash(stash, buffer, *readd);
		free(buffer);
	}
}

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (!stash)
		return ;
	linegen(line, stash);
	if (!(*line))
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->buf[i])
		{
			(*line)[j++] = stash->buf[i];
			if (stash->buf[i] == '\n')
				break ;
			i++;
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	cleanup(t_list **stash)
{
	t_list	*last;
	t_list	*cl;
	int		i;
	int		j;

	last = ft_lst_get_last(*stash);
	if ((!last->buf) || !(last->buf[0]))
		return ;
	cl = (t_list *)malloc(sizeof(t_list));
	if (!cl)
		return ;
	i = 0;
	while ((last->buf) && (last->buf[i] != '\n'))
		i++;
	if ((last->buf) && (last->buf[i] == '\n'))
		i++;
	*cl = (t_list){.buf = malloc(ft_strlen(last->buf) - i + 1), .next = NULL};
	if (!cl->buf)
		return ;
	j = 0;
	while (last->buf[i])
		cl->buf[j++] = last->buf[i++];
	cl->buf[j] = '\0';
	free_stash(*stash);
	*stash = cl;
}

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;
	int				readd;

	if ((fd < 0) || (BUFFER_SIZE < 1) || (read(fd, &line, 0) < 0))
		return (NULL);
	readd = 1;
	line = NULL;
	read_and_stash(fd, &stash, &readd);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	cleanup(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
