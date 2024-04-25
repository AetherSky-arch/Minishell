/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:18:28 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/25 02:09:45 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*get_chunk_heap(int fd, char *keep);
char	*init_chunk(char *keep);
void	clean_static(char *keep, int k);
size_t	fill_static(char *keep, char *next);

char	*gnl_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
void	*ft_calloc(size_t nb_elem, size_t size_in_oct);
char	*gnl_substr(char *str, unsigned int start, size_t lenght);
ssize_t	is_nl(char *str);

#endif