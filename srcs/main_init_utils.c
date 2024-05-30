/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 03:15:18 by aether            #+#    #+#             */
/*   Updated: 2024/05/30 15:45:17 by caguillo         ###   ########.fr       */
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
