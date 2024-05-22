/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:17:56 by aether            #+#    #+#             */
/*   Updated: 2024/05/22 00:08:53 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	temp_display_tabs(char **token, t_type *type)
{
	int		i;
	char	*t_type_names[] = {"INFILE", "OUTFILE", "OUTFAPP", "GREAT",
			"DGREAT", "LESS", "HEREDOC", "LIMITER", "PIPE", "CMD", "ARG", "EMPTY"};

	i = 0;
	printf("token:");
	while (token[i])
	{
		printf("%s / ", token[i]);
		i++;
	}
	// printf("%ld\n", ft_tabstr_len(token));
	// printf("%ld\n", ft_tabint_len(type));
	i = 0;
	printf("\n");
	// printf("type\n");
	// while (i < (int)ft_tabstr_len(token))
	// {
	// 	printf("%d / ", type[i]);
	// 	i++;
	// }
	// i = 0;
	// printf("\n");
	printf("type name:");
	while (i < (int)ft_tabstr_len(token))
	{
		printf("%s / ", t_type_names[type[i]]);
		i++;
	}
	printf("\n");
}

// size_t	ft_tabint_len(int *tab)
// {
// 	if (!tab)
// 		return (0);
// 	return (sizeof(tab) / sizeof(tab[0]));
// }

// size_t	ft_tabtype_len(t_type *tab)
// {
// 	if (!tab)
// 		return (0);
// 	return (sizeof(tab) / sizeof(tab[0]));
// }
