/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:40:39 by arguez            #+#    #+#             */
/*   Updated: 2024/02/08 16:20:55 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
void	add_to_stash(t_list **stash, char *buffer, int readd);
void	read_and_stash(int fd, t_list **stash, int *readd);
void	extract_line(t_list *stash, char **line);
void	clean_stash(t_list **stash);
void	free_stash(t_list *stash);
t_list	*ft_lst_get_last(t_list *stash);
int		found_newline(t_list *stash);
void	linegen(char **line, t_list *stash);

#endif
