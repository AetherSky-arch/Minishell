/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 03:15:18 by aether            #+#    #+#             */
/*   Updated: 2024/05/31 16:17:38 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main_init_utils(int *pexit, int *gvar, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	*pexit = 0;
	*gvar = 0;
}

static char	*append_space(char *str)
{
	char	*res;

	res = ft_strjoin(str, " ");
	free(str);
	return (res);
}

char	*chain_join(char **tab)
{
	char *res;
	char *tmp;
	int i;

	i = 0;
	res = ft_strdup("");
	while (tab[i] != NULL)
	{
		tmp = ft_strjoin(res, tab[i]);
		free(res);
		res = tmp;
		if (tab[i + 1] != NULL)
			res = append_space(res);
		i++;
	}
	return (res);
}
