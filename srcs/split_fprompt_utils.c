/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_fprompt_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 02:15:17 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/24 02:18:28 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**free_splits(char **split, int i, int j)
{
	while (j < i)
	{
		free(split[j]);
		j++;
	}
	free(split);
	return (NULL);
}
