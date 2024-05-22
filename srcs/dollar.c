/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:26:22 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/22 03:02:30 by caguillo         ###   ########.fr       */
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
	k = idx+1;
	while (str[k])
	{
		if (str[k] == '?' && k == idx + 1)
		{
			k++;
			break ;
		}		
		if (str[k] == '$' || str[k] == '=' || is_space(str[k]) == 1 || is_quote(str[k]) == 1)
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

static char	*get_vardoll(t_mini *mini, char *tok, int start)
{
	int		i;
	int		k;
	char	*varname;
	char	*varvalue;

	if (!tok)
		return (NULL);
	i = idx_dollar(tok, start);
	k = end_dollar(tok, start);
	// printf("k=%d\n", k);
	if (i < k)
	{
		varname = gnl_substr(tok, i + 1, k - i);
		// printf("varname :%s\n", varname);
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

static char	*expand_doll(t_mini *mini, char *tok, int start)
{
	char	*before;
	char	*after;
	char	*varvalue;
	char	*tmp;

	before = get_before(tok, start);
	// printf("before :%s\n", before);
	after = get_after(tok, start);
	// printf("after :%s\n", after);
	varvalue = get_vardoll(mini, tok, start);
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
		return (0);
	if (start == -1)
		return (0);
	i = start;
	if (i >= ft_strlen(str))
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (0);
}

void	check_dollar(t_mini *mini)
{
	int	i;
	int	idx;
	int start;

	//****securite + cas particulier*/
	i = 0;
	start = 0;
	while ((*mini).token[i])
	{
		// int j = 0;
		// while((*mini).token[i][j])
		// {
		// 	printf("%c = %d\n", (*mini).token[i][j],
		//	inside_quotes((*mini).token[i],j));
		// 	j++;
		// }
		idx = idx_dollar((*mini).token[i], start);
		// printf("idx %d\n", idx);
		if (idx != -1)
		{
			// printf("idx$ :%d\n", idx_dollar((*mini).token[i]));
			if (inside_quotes((*mini).token[i], idx) != 39)
			{
				(*mini).token[i] = expand_doll(mini, (*mini).token[i], start);
				// printf("empty :[%s]\n", (*mini).token[i]);
				// manage_empty(mini, (*mini).token[i]);
				// if (ft_strlen((*mini).token[i] == 0))
				// {
				// 	if (!(*mini).token[i+1])
				// 		(*mini).token[i] = NULL;
				// 	else
				// }
			}
		}
		if (inside_quotes((*mini).token[i], idx) == 39)
			idx = idx +1;
		// printf("%d\n", another_dollar(mini->token[i], idx));
		start = another_dollar(mini->token[i], idx);
		if (start == 0)
			i++;
		
			
		// if (idx_dollar((*mini).token[i]) == -1)
		// 	i++;
		// else
		// {
		// 	if ((inside_quotes((*mini).token[i],
		// 				idx_dollar((*mini).token[i])) == 39))
		// 		i++;
		// }
	}
}
