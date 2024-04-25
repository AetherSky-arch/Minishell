/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:18:18 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/25 02:02:41 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// chunk = soit nl dedans soit fin du fichier
// chunk = get_chunk(fd, keep) --> for the none-heap version
char	*get_next_line(int fd)
{
	static char	keep[BUFFER_SIZE + 1] = {0};
	char		*line;
	char		*chunk;
	char		*next;
	size_t		i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	chunk = get_chunk_heap(fd, keep);
	if (!chunk || chunk[0] == '\0')
		return (clean_static(keep, 0), free(chunk), NULL);
	if (is_nl(chunk) != -1)
	{
		line = gnl_substr(chunk, 0, is_nl(chunk) + 1);
		next = gnl_substr(chunk, is_nl(chunk) + 1, ft_strlen(chunk));
		free(chunk);
		if (!line || !next)
			return (clean_static(keep, 0), free(line), free(next), NULL);
		i = fill_static(keep, next);
		return (clean_static(keep, i), free(next), line);
	}
	else
		return (clean_static(keep, 0), chunk);
}

char	*get_chunk_heap(int fd, char *keep)
{
	char	*chunk;
	char	*buff;
	ssize_t	nbyte;
	int		eof;

	eof = 0;
	chunk = init_chunk(keep);
	if (!chunk)
		return (NULL);
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (free(chunk), NULL);
	while (is_nl(chunk) == -1 && eof == 0)
	{
		nbyte = read(fd, buff, BUFFER_SIZE);
		if (nbyte < 0)
			return (free(buff), free(chunk), NULL);
		if (nbyte < BUFFER_SIZE)
			eof = 1;
		buff[nbyte] = '\0';
		chunk = gnl_strjoin(chunk, buff);
	}
	free(buff);
	return (chunk);
}

char	*init_chunk(char *keep)
{
	char	*chunk;
	int		i;

	if (!keep)
		return (NULL);
	chunk = malloc((ft_strlen(keep) + 1) * sizeof(char));
	if (!chunk)
		return (NULL);
	i = 0;
	while (keep[i])
	{
		chunk[i] = keep[i];
		i++;
	}
	chunk[i] = '\0';
	return (chunk);
}

void	clean_static(char *keep, int k)
{
	int	i;

	i = k;
	while (i < BUFFER_SIZE + 1)
	{
		keep[i] = '\0';
		i++;
	}
}

size_t	fill_static(char *keep, char *next)
{
	size_t	i;

	i = 0;
	while (next[i])
	{
		keep[i] = next[i];
		i++;
	}
	return (i);
}

// char	*get_chunk(int fd, char *keep)
// {
// 	char	*chunk;
// 	char	buff[BUFFER_SIZE + 1] = {0};
// 	ssize_t	nbyte;
// 	int		eof;

// 	eof = 0;
// 	chunk = init_chunk(keep);
// 	if (!chunk)
// 		return (NULL);
// 	while (is_nl(chunk) == -1 && eof == 0)
// 	{
// 		nbyte = read(fd, buff, BUFFER_SIZE);
// 		if (nbyte < 0)
// 			return (free(chunk), NULL);
// 		if (nbyte < BUFFER_SIZE)
// 			eof = 1;
// 		buff[nbyte] = '\0';
// 		chunk = gnl_strjoin(chunk, buff);
// 	}
// 	return (chunk);
// }
