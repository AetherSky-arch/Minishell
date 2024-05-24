/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:46:38 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/24 01:47:22 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**create_hd_name(t_mini *mini)
{
	char	**hd_name;
	int		i;
	int		nb;

	nb = nbr_heredoc(*mini);
	if (nb > 16)
	{
		ft_putstr_fd(ERR_NHD, STD_ERR);
		free_close_exit(mini, EXIT_STX, 0);
	}
	hd_name = malloc(sizeof(char *) * (nb + 1));
	if (!hd_name)
	{
		ft_putstr_fd(ERR_MAL, STD_ERR);
		return (mini->exitcode = EXIT_FAILURE, NULL);
	}
	i = 0;
	while (i < nb)
	{
		hd_name[i] = NULL;
		i++;
	}
	hd_name[i] = NULL;
	return (hd_name);
}

char	*heredoc_name(void)
{
	char				*name;
	unsigned long int	nbr;
	char				*number;

	nbr = 0;
	name = NULL;
	while (nbr < ULONG_MAX)
	{
		number = ft_ulitoa(nbr);
		name = ft_strjoin("/tmp/heredoc_", number);
		free(number);
		if (name)
		{
			if (access(name, F_OK) != 0)
				break ;
		}
		nbr++;
		free(name);
	}
	return (name);
}
