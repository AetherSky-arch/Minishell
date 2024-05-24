/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:48:00 by aether            #+#    #+#             */
/*   Updated: 2024/05/03 18:17:00 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**double_dup(char **tab)
{
	char	**copy;
	int		i;

	if (tab == NULL)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
		i++;
	copy = malloc((i + 1) * sizeof(char *));
	if (copy == NULL)
	{
		ft_putstr_fd("double_dup: malloc error\n", 2);
		return (NULL);
	}
	i = 0;
	while (tab[i] != NULL)
	{
		copy[i] = ft_strdup(tab[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
