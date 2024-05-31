/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:07:30 by aether            #+#    #+#             */
/*   Updated: 2024/05/31 02:06:09 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// check_syntax return: 1 on failure (error), 0 on success (no error)
int	check_syntax(t_mini *mini)
{
	char	*tmp1;
	char	*tmp2;

	if (check_pipe(mini) == FAILURE)
	{
		if (mini->token[mini->stx_err_idx])
		{
			tmp1 = ft_strjoin(ERR_HDX, mini->token[mini->stx_err_idx]);
			tmp2 = ft_strjoin(tmp1, "'\n");
			ft_putstr_fd(tmp2, STD_ERR);
			free(tmp1);
			free(tmp2);
		}
		else
			ft_putstr_fd(ERR_STX, STD_ERR);
		mini->exitcode = EXIT_STX;
		return (FAILURE);
	}
	if (check_type_sequence(mini) == FAILURE)
		return (FAILURE);
	return (check_heredoc(mini));
}

int	check_pipe(t_mini *mini)
{
	int	i;

	if (!mini->type)
		return (FAILURE);
	i = 0;
	while (i < mini->type_len)
	{
		if (mini->type[i] == PIPE)
		{
			if (i == 0)
				return (mini->stx_err_idx = i, FAILURE);
			if (mini->type[i - 1] == PIPE)
				return (mini->stx_err_idx = i, FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static int	sub_check_type_sequence(t_mini *mini, int *i)
{
	char	*tmp;

	if (!mini->token[*i + 1])
	{
		tmp = ft_strjoin(ERR_HDX, "newline");
		mini->stx_err_idx = *i;
		(ft_putstr_fd(tmp, STD_ERR), ft_putstr_fd("'\n", STD_ERR));
		free(tmp);
		mini->exitcode = EXIT_STX;
		return (FAILURE);
	}
	if ((GREAT <= mini->type[*i + 1] && mini->type[*i + 1] <= HEREDOC)
		|| (mini->type[*i + 1] == PIPE) || (*i + 1 == mini->type_len))
	{
		if (*i + 1 == mini->type_len)
			tmp = ft_strjoin(ERR_HDX, "newline");
		else
			tmp = ft_strjoin(ERR_HDX, mini->token[*i + 1]);
		mini->stx_err_idx = *i + 1;
		(ft_putstr_fd(tmp, STD_ERR), ft_putstr_fd("'\n", STD_ERR));
		free(tmp);
		mini->exitcode = EXIT_STX;
		return (FAILURE);
	}
	return (SUCCESS);
}

// must be after create type
int	check_type_sequence(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->token[i])
	{
		if (GREAT <= mini->type[i] && mini->type[i] <= HEREDOC)
		{
			if (sub_check_type_sequence(mini, &i) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
