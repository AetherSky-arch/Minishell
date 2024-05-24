/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:26:44 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/24 00:27:39 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_cmd_idx(t_mini mini, int start)
{
	int	i;
	int	cmd_idx;

	cmd_idx = ft_tabstr_len(mini.token);
	i = start;
	while ((i < mini.type_len) && (mini.type[i] != PIPE))
	{
		if (mini.type[i] == CMD)
		{
			cmd_idx = i;
			break ;
		}
		i++;
	}
	return (cmd_idx);
}

int	ft_tabstr_len(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}
