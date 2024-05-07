/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:43:09 by aether            #+#    #+#             */
/*   Updated: 2024/05/07 19:07:41 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	envvars_manager(char **tokens, t_mini *mini, int prev_exit)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strcmp(tokens[i], "$?") == 0)
		{
			free(tokens[i]);
			tokens[i] = ft_itoa(prev_exit);
		}
		else if (tokens[i][0] == '$')
		{
			tmp = ft_strdup(tokens[i]);
			free(tokens[i]);
			tmp++;
			tokens[i] = ft_getenv(mini, tmp);
			tmp--;
			free(tmp);
		}
		i++;
	}
}
