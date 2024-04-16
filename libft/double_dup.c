/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:48:00 by aether            #+#    #+#             */
/*   Updated: 2024/04/16 17:51:48 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char  **double_dup(char **tab)
{
    char  **copy;
    int   i;

    if (tab == NULL)
        return (NULL);
    i = 0;
    while (tab[i] != NULL)
        i++;
    copy = malloc(i * sizeof(char *));
    if (copy == NULL)
        return (NULL);
    while (tab[i] != NULL)
    {
        copy[i] = ft_strdup(tab[i]);
        i++;
    }
    copy[i] = NULL;
    return (copy);
}
