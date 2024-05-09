/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:43:09 by aether            #+#    #+#             */
/*   Updated: 2024/05/09 23:36:39 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ' = do nothing //" = change $ with value
void	envvars_manager(char **tokens, t_mini *mini, int prev_exit)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tokens[i] != NULL)
	{
		while (tokens[i][0] == '$')
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
