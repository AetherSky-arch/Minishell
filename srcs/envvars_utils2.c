/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ae7th <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:27:38 by ae7th             #+#    #+#             */
/*   Updated: 2024/05/16 15:39:58 by ae7th            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void reset_fne_vars(int *sp_i, int *i)
{
    *sp_i = 0;
    *i = 0;
}

static int  fne_checkfor_sp_i_increment(t_trash trash)
{
    int i;

    i = trash.i;
    while (i >= 0)
    {
        if (trash.formats[i] == 'v')
            return (1);
        i--;
    }
    return (0);
}

static char *fne_getenv_subroutine(char *str, t_mini *mini, int i, int j)
{
    char  *tmp;
    char  *res;

    tmp = ft_substr(str, 0, i - j);
    res = ft_getenv(mini, tmp);
    free(tmp);
    return (res);
}

char  *find_next_element(char *token, t_trash *trash, t_mini *mini)
{
    static int  i = 0;
    int  j = 0;
    static int  splitted_index = 0;

    if (trash->i == 0)
        reset_fne_vars(&splitted_index, &i);
    if (trash->formats[trash->i] == 's')
    {
        if (fne_checkfor_sp_i_increment(*trash) == 0)
            splitted_index++;
        trash->i++;
        j = i;
        while ((token[i] != '$') && (token[i] != '\0'))
            i++;
        while ((token[i] == '$') && (token[i + 1] == '$'))
            i++;
        return (ft_substr(token, j, i - j));
    }
    i++;
    j = i;
    while ((token[i] != ' ') && (token[i] != '$') && (token[i] != '\0'))
        i++;
    splitted_index++;
    trash->i++;
    return (fne_getenv_subroutine(trash->splitted[splitted_index - 1], mini, i, j));
}
