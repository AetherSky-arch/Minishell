/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:26:22 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/31 15:25:31 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_varvalue(char **tab, char *str)
{
	int	i;

	i = 0;
	while (ft_strncmp(tab[i], str, ft_strlen(str)) != 0)
		i++;
	return (gnl_substr(tab[i], ft_strlen(str) + 1, ft_strlen(tab[i])));
}

// *stop = is_loop(varname, varvalue);
// free(varname);
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
	return (*stop = is_loop(varname, varvalue), free(varname), varvalue);
}

static char	*exp_do(t_mini *mini, char *tok, int start, int *stop)
{
	char	*before;
	char	*after;
	char	*varvalue;
	char	*tmp;

	before = get_before(tok, start);
	after = get_after(tok, start);
	varvalue = get_vardoll(mini, tok, start, stop);
	free(tok);
	tmp = ft_strjoin(before, varvalue);
	free(before);
	free(varvalue);
	tok = ft_strjoin(tmp, after);
	free(tmp);
	free(after);
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
