/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:28:48 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/26 01:31:58 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*** after parsing $ and arg to get the real name of the cmd set after check in token***/
int	is_builtin(t_mini mini, int start)
{
	char	*builtins[] = {"cd", "echo", "env", "exit", "export", "pwd",
			"unset"};
	int		i;
	int		k;

	i = start;
	while ((i < mini.type_len) && (mini.type[i] != PIPE))
	{
		if (mini.type[i] == CMD)
		{
			k = 0;
			while (k < 7)
			{
				if (ft_strcmp(mini.token[i], builtins[k]) == 0)
					return (k);
				k++;
			}
		}
		i++;
	}
	return (-1);
}

/*** malloc to be free'd***/
char	**create_block(t_mini mini, int start)
{
	char	**block;
	int		i;

	block = malloc(sizeof(char *) * (len_block(mini, start) + 1));
	if (!block)
		return (NULL);
	i = 0;
	while ((i < mini.type_len) && (mini.type[i] != PIPE))
	{
		block[i] = mini.token[i + start];
		i++;
	}
	block[i] = NULL;
	return (block);
}

int	len_block(t_mini mini, int start)
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while ((i < mini.type_len) && (mini.type[i] != PIPE))
	{
		if (mini.token[i])
			count++;
	}
	return (count);
}

void	parent(t_mini *mini, char **args, int start)
{
	int	k;

	k = is_builtin(*mini, start);
	if (k == ECHO)
		echo(args);
}
