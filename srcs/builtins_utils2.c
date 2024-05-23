/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:49:44 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/24 00:05:02 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_arg(t_mini *mini, int i, int *j)
{
	if (mini->type[i] == ARG)
	{
		mini->cmd_arg[*j] = ft_strdup(mini->token[i]);
		*j = *j + 1;
	}
}

// same as get_cmd_arg in exec.c
void	create_cmd_arg(t_mini *mini, int start)
{
	int	i;
	int	j;

	mini->cmd_arg = malloc(sizeof(char *) * (len_cmd_arg(*mini, start) + 1));
	if (!mini->cmd_arg)
		return ;
	i = start;
	j = 0;
	while ((i < mini->type_len) && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == CMD)
		{
			mini->cmd_arg[j] = ft_strdup(mini->token[i]);
			i++;
			j++;
			while ((i < mini->type_len) && (mini->type[i] != PIPE))
			{
				add_arg(mini, i, &j);
				i++;
			}
			break ;
		}
		i++;
	}
	mini->cmd_arg[j] = NULL;
}

int	len_cmd_arg(t_mini mini, int start)
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while ((i < mini.type_len) && (mini.type[i] != PIPE))
	{
		if (mini.type[i] == CMD)
		{
			i++;
			count++;
			while ((i < mini.type_len) && (mini.type[i] != PIPE))
			{
				if (mini.type[i] == ARG)
					count++;
				i++;
			}
			break ;
		}
		i++;
	}
	return (count);
}
