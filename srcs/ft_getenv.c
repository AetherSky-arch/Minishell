/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ae7th <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:56:39 by ae7th             #+#    #+#             */
/*   Updated: 2024/05/15 22:03:06 by ae7th            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *get_exitcode(t_mini *mini, char *varname)
{
    char  *res;
    char  *tmp;
    char  *tmp2;

    tmp = ft_itoa(mini->exitcode);
    if (ft_strlen(varname) == 1)
        return (tmp);
    tmp2 = ft_strdup(varname + 1);
    res = ft_strjoin(tmp, tmp2);
    free(tmp);
    free(tmp2);
    return (res);
}

char	*ft_getenv(t_mini *mini, char *varname)
{
	int	i;
	int	j;

	i = 0;
    if (varname[0] == '?')
    {
        return (get_exitcode(mini, varname));
    }
	while (mini->envvars[i] != NULL)
	{
		j = 0;
		while (mini->envvars[i][j] != '=')
			j++;
		if (ft_strncmp(varname, mini->envvars[i], j) == 0)
			return (ft_substr(mini->envvars[i], j + 1,
					ft_strlen(mini->envvars[i])));
		i++;
	}
	return (ft_strdup(""));
}
