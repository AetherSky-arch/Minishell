/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:34:53 by aether            #+#    #+#             */
/*   Updated: 2024/04/27 00:12:25 by caguillo         ###   ########.fr       */
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
		return (chd_putstr_error(path, ERR_DIR), 1);
	else if (checkfor_dir(path) == 0)
		return (chd_putstr_error(path, ": Not a directory\n"), 1);
	else
	{
		if (chdir(path) != 0)
			return (ft_putstr_fd("minishell: cd: chdir function failed\n",
					STD_ERR), 1);
		return (0);
	}
}

void	chd_putstr_error(char *path, char *err_str)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("minishell: cd: ", path);
	tmp2 = ft_strjoin(tmp1, err_str);
	ft_putstr_fd(tmp2, STD_ERR);
	free(tmp1);
	free(tmp2);
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
