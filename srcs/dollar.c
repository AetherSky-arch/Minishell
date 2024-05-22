/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:26:22 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/22 21:05:23 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	idx_dollar(char *str, int start)
{
	size_t	i;

	if (!str)
		return (-1);
	i = start;
	if (i >= ft_strlen(str))
		return (-1);
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == 0)
				return (-1);
			if (is_space(str[i + 1]) == 1)
				return (-1);
			if (is_quote(str[i + 1]) == 1)
				return (-1);
			if (str[i + 1] == '=')
				return (-1);
			if (str[i + 1] != '$')
				return (i);
		}
		i++;
	}
	return (-1);
}

static int	end_dollar(char *str, int start)
{
	int	k;
	int	idx;

	if (!str)
		return (0);
	idx = idx_dollar(str, start);
	k = idx + 1;
	while (str[k])
	{
		if (str[k] == '?' && k == idx + 1)
		{
			k++;
			break ;
		}
		if (str[k] == '$' || str[k] == '=' || is_space(str[k]) == 1
			|| is_quote(str[k]) == 1)
			break ;
		k++;
	}
	return (k - 1);
}

static char	*get_varvalue(char **tab, char *str)
{
	int	i;

	i = 0;
	while (ft_strncmp(tab[i], str, ft_strlen(str)) != 0)
		i++;
	return (gnl_substr(tab[i], ft_strlen(str) + 1, ft_strlen(tab[i])));
}

static int	is_loop(char *varname, char *varvalue)
{
	char	*tmp;

	tmp = ft_strjoin("$", varname);
	if (ft_strcmp(tmp, varvalue) == 0)
		return (free(tmp), 1);
	return (free(tmp), 0);
}

static char	*get_vardoll(t_mini *mini, char *tok, int start, int *stop)
{
	int		i;
	int		k;
	char	*varname;
	char	*varvalue;

	if (!tok)
		return (NULL);
	i = idx_dollar(tok, start);
	k = end_dollar(tok, start);
	if (i < k)
	{
		varname = gnl_substr(tok, i + 1, k - i);
	}
	else
		return (NULL);
	if (ft_strcmp(varname, "?") == 0)
		varvalue = ft_itoa(mini->lastcode);
	else
	{
		if (is_in_twod((*mini).envvars, varname) == 1)
			varvalue = get_varvalue((*mini).envvars, varname);
		else
			varvalue = ft_strdup("");
	}
	*stop = is_loop(varname, varvalue);
	free(varname);
	return (varvalue);
}

static char	*get_before(char *tok, int start)
{
	int		i;
	char	*before;

	if (!tok)
		return (NULL);
	i = idx_dollar(tok, start);
	if (i > 0)
		before = gnl_substr(tok, 0, i);
	else
		before = ft_strdup("");
	return (before);
}

static char	*get_after(char *tok, int start)
{
	int		k;
	char	*after;

	if (!tok)
		return (NULL);
	k = end_dollar(tok, start);
	if ((unsigned int)k < ft_strlen(tok) - 1)
		after = gnl_substr(tok, k + 1, ft_strlen(tok));
	else
		after = ft_strdup("");
	return (after);
}

static char	*exp_do(t_mini *mini, char *tok, int start, int *stop)
{
	char	*before;
	char	*after;
	char	*varvalue;
	char	*tmp;

	before = get_before(tok, start);
	// printf("before :%s\n", before);
	after = get_after(tok, start);
	// printf("after :%s\n", after);
	varvalue = get_vardoll(mini, tok, start, stop);
	// printf("varvalue :%s\n", varvalue);
	free(tok);
	tmp = ft_strjoin(before, varvalue);
	free(before);
	free(varvalue);
	tok = ft_strjoin(tmp, after);
	free(tmp);
	free(after);
	// printf("newtok :%s\n", tok);
	return (tok);
}

static int	another_dollar(char *str, int start)
{
	size_t	i;

	if (!str)
		return (-1);
	if (start == -1)
		return (-1);
	i = start;
	if (i >= ft_strlen(str))
		return (-1);
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	check_dollar(t_mini *mini)
{
	int	i;
	int	idx;
	int	start;
	int	stop;

	if (!(*mini).token)
		return ;
	i = 0;
	start = 0;
	stop = 0;
	while ((*mini).token[i])
	{
		idx = idx_dollar((*mini).token[i], start);
		if (idx != -1)
		{
			if (inside_quotes((*mini).token[i], idx) != 39)
				(*mini).token[i] = exp_do(mini, (*mini).token[i], start, &stop);
		}
		if (inside_quotes((*mini).token[i], idx) == 39 || stop == 1)
			idx = idx + 1;
		start = another_dollar(mini->token[i], idx);
		if (start == -1)
		{
			i++;
			start = 0;
		}
	}
}

/****draft */

// 0 il est en 0

// printf("idx$ :%d\n", idx);

// if (idx_dollar((*mini).token[i]) == -1)
// 	i++;
// else
// {
// 	if ((inside_quotes((*mini).token[i],
// 				idx_dollar((*mini).token[i])) == 39))
// 		i++;
// }
// printf("empty :[%s]\n", (*mini).token[i]);
// manage_empty(mini, (*mini).token[i]);
// if (ft_strlen((*mini).token[i] == 0))
// {
// 	if (!(*mini).token[i+1])
// 		(*mini).token[i] = NULL;
// 	else
// }
// printf("%d\n", another_dollar(mini->token[i], idx));

//&& idx_dollar((*mini).token[i], idx) == -1)