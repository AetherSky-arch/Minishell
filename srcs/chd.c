/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:34:53 by aether            #+#    #+#             */
/*   Updated: 2024/05/16 01:57:57 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// return 0 if not a directory
int	checkfor_dir(t_mini *mini, char *path)
{
	struct stat	statbuf;

	if (path)
	{
		if (stat(path, &statbuf) == -1)		
			perror_close_exit("minishell: stat", mini, EXIT_FAILURE);			
		return (S_ISDIR(statbuf.st_mode));
	}
	return (0);
}

/*** Need to close fd's in case of error ? ***/
int	ft_chd(t_mini *mini)
{
	char	*homedir;

	if (mini->cmd_arg[1] && mini->cmd_arg[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (mini->cmd_arg[1])
	{
		if (access(mini->cmd_arg[1], F_OK) != 0)
			return (chd_str_err(mini->cmd_arg[1], ERR_DIR), 1);
		else if (checkfor_dir(mini, mini->cmd_arg[1]) == 0)
			return (chd_str_err(mini->cmd_arg[1], ": Not a directory\n"), 1);
		else
		{
			if (chdir(mini->cmd_arg[1]) != 0)
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
