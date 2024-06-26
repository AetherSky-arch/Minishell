/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:23:32 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/23 21:26:46 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_twod(char **tab, char *str)
{
	int	j;
	int	i;
	int	n;

	if (is_equal(str) == 1)
	{
		j = 0;
		while (str[j] != '=')
			j++;
		n = j;
	}
	else
		n = ft_strlen(str);
	if (tab)
	{
		i = 0;
		while (tab[i] != NULL)
		{
			if (ft_strncmp(tab[i], str, n) == 0)
				return (1);
			i++;
		}
	}
	return (0);
}

int	is_as_child(t_mini mini)
{
	int	i;

	i = 0;
	while (i < mini.type_len)
	{
		if (mini.type[i] == PIPE)
			return (1);
		i++;
	}
	return (0);
}
