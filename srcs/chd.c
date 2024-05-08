/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:34:53 by aether            #+#    #+#             */
/*   Updated: 2024/05/08 22:57:38 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// return 0 if not a directory
int	checkfor_dir(char *path)
{
	struct stat	statbuf;

	if (path)
	{
		stat(path, &statbuf);
		return (S_ISDIR(statbuf.st_mode));
	}
	return (0);
}

/*** Need to close fd's in case of error ? ***/
int	ft_chd(t_mini *mini, char *path)
{
	char	*homedir;

	if (path)
	{
		if (access(path, F_OK) != 0)
			return (chd_str_err(path, ERR_DIR), 1);
		else if (checkfor_dir(path) == 0)
			return (chd_str_err(path, ": Not a directory\n"), 1);
		else
		{
			if (chdir(path) != 0)
				return (perror("minishell: chdir"), 1);
			return (0);
		}
	}
	else
	{
		homedir = ft_getenv(mini, "HOME");
		if (homedir)
		{
			if (chdir(homedir) != 0)
				return (free(homedir), perror("minishell: chdir"), 1);
			return (free(homedir), 0);
		}
		else
			return (free(homedir), chd_str_err("No HOME variable", "\n"), 1);
	}
}

void	chd_str_err(char *path, char *err_str)
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

//return (ft_putstr_fd("minishell: cd: chdir function failed\n",STD_ERR), 1);
*/
