/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aether <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:34:53 by aether            #+#    #+#             */
/*   Updated: 2024/04/12 17:22:33 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	checkfor_dir(char *path)
{
	struct stat	statbuf;

	stat(path, &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}

int	chd(char *path)
{
	if (access(path, F_OK) != 0)
		return (ft_putstr_fd("cd: no such file or directory\n", 2), 1);
    else if (checkfor_dir(path) == 0)
        return (ft_putstr_fd("cd: not a directory\n", 2), 1);
    else
    {
	    if (chdir(path) != 0)
		    return (ft_putstr_fd("chdir function failed\n", 2), 1);
	    return (0);
    }
}

/*
int	main(int argc, char **argv)
{
	if (argc != 2)
    {
        ft_putstr_fd("cd: expected 1 argument\n", 2);
		return (1);
    }
	return (chd(argv[1]));
}
*/
