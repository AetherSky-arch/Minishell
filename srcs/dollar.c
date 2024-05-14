/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 04:11:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/14 04:40:46 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_doll(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
		}
	}
}

// 0 false, 1 true
int	is_in_quote(char q, char *str, int k)
{
	int i;
	int open;

	if (!str)
		return (0);
	i = 0;
    open = 0;
	while (str[i])
	{
		if (str[i] == q && i < k)
            open++;
        i++;    
	}
    return(open % 2);
}