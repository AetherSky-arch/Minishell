/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:39:31 by arguez            #+#    #+#             */
/*   Updated: 2024/02/08 15:58:26 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>
# include "libft.h"

void	ft_hexa(long n, char format);
int		ft_putptr(uintptr_t n, char format);
int		ft_hexput(long n, char format);
int		ft_putunsigned(unsigned int n);
int		ft_putstr_fd(char *str, int fd);
int		ft_numput(int n, int fd);
int		ft_printf(const char *format, ...);

#endif
