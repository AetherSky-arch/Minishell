/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:43:09 by aether            #+#    #+#             */
/*   Updated: 2024/05/06 14:20:41 by aether           ###   ########.fr       */
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
        if (ft_strcmp(tokens[i], "$?") == 0)
            tokens[i] = ft_itoa(mini->exitcode);
        else if (tokens[i][0] == '$')
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
