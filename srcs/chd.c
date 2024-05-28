/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:34:53 by aether            #+#    #+#             */
/*   Updated: 2024/05/28 01:40:52 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// return 0 if not a directory
int	checkfor_dir(char *path)
{
	struct stat	statbuf;

	if (path)
	{
		if (stat(path, &statbuf) == -1)
			return (perror("minishell: stat"), 0);
		return (S_ISDIR(statbuf.st_mode));
	}
	return (0);
}

static int	cd_with_arg(t_mini *mini)
{
	char	*pwd;

	if (access(mini->cmd_arg[1], F_OK) != 0)
		return (chd_str_err(mini->cmd_arg[1], ERR_DIR), 1);
	else if (checkfor_dir(mini->cmd_arg[1]) == 0)
		return (chd_str_err(mini->cmd_arg[1], ": Not a directory\n"), 1);
	else
	{
		if (chdir(mini->cmd_arg[1]) != 0)
			return (perror("minishell: chdir"), 1);		
		pwd = ft_getenv(mini, "PWD");
		// if (ft_strcmp(pwd, "") != 0) // condition utile ???
		update_pwd(mini, "OLDPWD=", pwd);
		free(pwd);		
		pwd = get_pwd();
		if (pwd)
			update_pwd(mini, "PWD=", pwd);
		free(pwd);		
		return (0);
	}
}

static int	cd_no_arg(t_mini *mini)
{
	char	*homedr;
	char	*pwd;

	homedr = ft_getenv(mini, "HOME");
	if (homedr)
	{
		if (chdir(homedr) != 0)
			return (free(homedr), perror("minishell: chdir"), 1);
		pwd = ft_getenv(mini, "PWD");
		// if (ft_strcmp(pwd, "") != 0) // condition utile ???
		update_pwd(mini, "OLDPWD=", pwd);
		free(pwd);
		update_pwd(mini, "PWD=", homedr);
		return (free(homedr), 0);
	}
	else
		return (free(homedr), chd_str_err("No HOME variable", "\n"), 1);
}

int	ft_chd(t_mini *mini)
{
	if (mini->cmd_arg[1] && mini->cmd_arg[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (mini->cmd_arg[1])
		return (cd_with_arg(mini));
	else
		return (cd_no_arg(mini));
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
