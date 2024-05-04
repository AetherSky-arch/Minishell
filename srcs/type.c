/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:58:45 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/04 00:16:22 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/****************malloc to be free'd***********/
t_type	*create_type(t_mini *mini)
{
	t_type	*type;
	int		i;

	if (!(*mini).token)
		return (NULL);
	(*mini).type_len = ft_tabstr_len((*mini).token);
	// type = malloc(sizeof(t_type) * (*mini).type_len);
	type = malloc(sizeof(int) * (*mini).type_len);
	if (!type)
		return (NULL);
	i = 0;
	while ((*mini).token[i])
	{
		type[i] = get_type((*mini).token, i);
		i++;
	}
	return (type);
}

t_type	get_type(char **token, int i)
{
	if (ft_strcmp(token[i], "<") == 0)
		return (LESS);
	else if (ft_strcmp(token[i], "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(token[i], ">") == 0)
		return (GREAT);
	else if (ft_strcmp(token[i], ">>") == 0)
		return (DGREAT);
	else if (ft_strcmp(token[i], "|") == 0)
		return (PIPE);
	else if (i > 0 && token[i - 1] && ft_strcmp(token[i - 1], "<") == 0)
		return (INFILE);
	else if (i > 0 && token[i - 1] && ft_strcmp(token[i - 1], "<<") == 0)
		return (LIMITER);
	else if (i > 0 && token[i - 1] && ft_strcmp(token[i - 1], ">") == 0)
		return (OUTFILE);
	else if (i > 0 && token[i - 1] && ft_strcmp(token[i - 1], ">>") == 0)
		return (OUTFAPP);
	else if (i > 0 && token[i - 1] && ft_strcmp(token[i - 1], "|") == 0)
		return (CMD);
	else
		return (get_type2(token, i));
}

t_type	get_type2(char **token, int i)
{
	if (i == 0)
		return (CMD);
	else if (token[i + 1] && ft_strcmp(token[i + 1], "|") == 0)
	{
		if (access(token[i], X_OK) == 0)
			return (CMD);
		else
			return (ARG);
	}
	else
		return (ARG);
}

// why that case ? it fails this one for example :
// echo titi < out >> out toto --> so no
// for that case : << eof cat --> so yes after fixed
void	check_type(t_mini *mini)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	start = 0;
	j = 0;	
	while (i < nbr_block(*mini))
	{
		check_type_block(mini, start);
		while ((j < mini->type_len) && (mini->type[j] != PIPE))
			j++;
		if (j < mini->type_len)
			j++;	
		start = j;
		i++;
	}
}

// ARG --> CMD and // CMD --> ARG
void	check_type_block(t_mini *mini, int start)
{
	int	i;
	int	cmd_idx;

	if (!(mini->type) || !(mini->token))
		return ;
	cmd_idx = get_cmd_idx(*mini, start);
	i = start;
	while ((i < mini->type_len) && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == ARG && i < cmd_idx)
		{
			mini->type[i] = CMD;
			cmd_idx = i;
		}
		i++;
	}
	i = start;
	while ((i < mini->type_len) && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == CMD && i > cmd_idx)
			mini->type[i] = ARG;
		i++;
	}
}

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

// draft

// void	check_type(t_type *type, char **token)
// {
// 	int	i;

// 	if (!type || !token)
// 		return ;
// 	i = 0;
// 	while (i < ft_tabstr_len(token))
// 	{
// 		if (type[i] == ARG)
// 		{
// 			if (i > 0 && (type[i - 1] == INFILE || type[i - 1] == OUTFILE
// 					|| type[i - 1] == OUTFAPP || type[i - 1] == LIMITER))
// 				type[i] = CMD;
// 		}
// 		i++;
// 	}
// }
