/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:43:09 by aether            #+#    #+#             */
/*   Updated: 2024/05/03 17:57:44 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void  envvars_manager(char **tokens, t_mini *mini)
{
    int i;
    char  *tmp;

    i = 0;
    while (tokens[i] != NULL)
    {
        if (tokens[i][0] == '$')
        {
            tmp = tokens[i];
            tmp++;
            tokens[i] = ft_getenv(mini, tmp);
            tmp--;
            free(tmp);
        }
        i++;
    }
}
