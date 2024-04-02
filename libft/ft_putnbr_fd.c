/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: arguez <marvin@42.fr>			    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/11/08 14:49:26 by arguez	       #+#    #+#	      */
/*   Updated: 2023/11/08 14:53:25 by arguez           ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "libft.h"

static void	writer_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	new;

	new = n;
	if (n < 0)
	{
		writer_fd('-', fd);
		new = -n;
	}
	if (new >= 10)
	{
		ft_putnbr_fd(new / 10, fd);
		ft_putnbr_fd(new % 10, fd);
	}
	else
		writer_fd(new + '0', fd);
}
