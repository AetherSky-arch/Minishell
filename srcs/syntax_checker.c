/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:07:30 by aether            #+#    #+#             */
/*   Updated: 2024/05/13 19:35:35 by caguillo         ###   ########.fr       */
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

// must be after create type
int	check_type_sequence(t_mini *mini)
{
	int		i;
	char	*tmp;

	i = 0;
	while (mini->token[i])
	{
		if (GREAT <= mini->type[i] && mini->type[i] <= HEREDOC)
		{
			if ((i + 1 == mini->type_len) || (GREAT <= mini->type[i + 1]
					&& mini->type[i + 1] <= HEREDOC) || (mini->type[i
					+ 1] == PIPE))
			{
				if (i + 1 == mini->type_len)
					tmp = ft_strjoin(ERR_HDX, "newline");
				else
					tmp = ft_strjoin(ERR_HDX, mini->token[i + 1]);
				mini->stx_err_idx = i + 1;
				ft_putstr_fd(tmp, STD_ERR);
				ft_putstr_fd("'\n", STD_ERR);
				free(tmp);
				mini->exitcode = EXIT_STX;
				return (FAILURE);
			}
		}
		i++;
	}
	return (SUCCESS);
}

// char	get_next_char(char *prompt, int i)
// {
// 	i++;
// 	while ((prompt[i] == ' ') && (prompt[i] != '\0'))
// 		i++;
// 	return (prompt[i]);
// }

// int	count_less_more(char *prompt, int *i)
// {
// 	char	original;
// 	int		res;

// 	original = prompt[*i];
// 	res = 1;
// 	while (get_next_char(prompt, *i) == original)
// 	{
// 		*i = *i + 1;
// 		res++;
// 	}
// 	if (res > 2)
// 		return (0);
// 	return (1);
// }

// int	check_less_more(char *str)
// {
// 	int	j;

// 	j = 0;
// 	while (str[j] != '\0')
// 	{
// 		if ((str[j] == '>') || (str[j] == '<'))		
// 		{
// 			if (count_less_more(str, &j) == 0)
// 				return (0);
// 		}
// 		j++;
// 	}
// 	return (1);
// }

// // <> and >< cases
// int	check_less_and_more(char *str)
// {
// 	int	j;

// 	j = 0;
// 	while (str[j] != '\0')
// 	{
// 		if (str[j] == '>')
// 		{
// 			if (str[j + 1] && (str[j + 1] == '<'))
// 				return (0);
// 		}
// 		if (str[j] == '<')
// 		{
// 			if (str[j + 1] && (str[j + 1] == '>'))
// 				return (0);
// 		}
// 		j++;
// 	}
// 	return (1);
// }

// int	check_less_more_pipe(char *str)
// {
// 	int	j;

// 	j = 0;
// 	while (str[j] != '\0')
// 	{
// 		if (str[j] == '>' || str[j] == '<')
// 		{
// 			if (str[j + 1] && (str[j + 1] == '|'))
// 				return (0);
// 		}
// 		if (str[j] == '|')
// 		{
// 			if (str[j + 1] && ((str[j + 1] == '<') || (str[j + 1] == '>')))
// 				return (0);
// 		}
// 		j++;
// 	}
// 	return (1);
// }

// // syntax_checker return: 1 on failure (error), 0 on success (no error)
// // others return boolean, 0 faux, 1 vrai
// int	syntax_checker(t_mini *mini)
// {
// 	// int	i;

// 	// i = 0;
// 	if (check_pipe(mini) == 0)
// 		return (FAILURE);
// 	// while (mini->token[i])
// 	// {
// 	// 	//|| check_less_more_pipe(mini->token[i]) == 0)
// 	// 	// || check_less_and_more(mini->token[i]) == 0)
// 	// 	if (check_less_more(mini->token[i]) == 0)
// 	// 	{
// 	// 		mini->stx_err_idx = i;
// 	// 		return (FAILURE);
// 	// 	}
// 	// 	i++;
// 	// }
// 	return (SUCCESS);
// }

// int	check_pipes(t_mini *mini)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (mini->token[i])
// 	{
// 		j = 0;
// 		while (mini->token[i][j] != '\0')
// 		{
// 			if (mini->token[i][j] == '|')
// 			{
// 				if (get_next_char(mini->token[i], j) == '|')
// 				{
// 					mini->stx_err_idx = i;
// 					return (0);
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// int	check_less_more(t_mini *mini)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (mini->token[i])
// 	{
// 		j = 0;
// 		while (mini->token[i][j] != '\0')
// 		{
// 			if ((mini->token[i][j] == '>') || (mini->token[i][j] == '<'))
// 			{
// 				if (count_less_more(mini->token[i], &j) == 0)
// 				{
// 					mini->stx_err_idx = i;
// 					return (0);
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1);
// }
