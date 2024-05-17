/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:28:48 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/17 21:33:33 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*** after parsing $ and arg to get the real name of the cmd set after check in token***/
int	is_builtin(t_mini mini, int start)
{
	char	*builtins[] = {"cd", "echo", "env", "exit", "export", "pwd",
			"unset"};
	int		i;
	int		k;

	i = start;
	while ((i < mini.type_len) && (mini.type[i] != PIPE))
	{
		if (mini.type[i] == CMD)
		{
			k = 0;
			while (k < 7)
			{
				if (ft_strcmp(mini.token[i], builtins[k]) == 0)
					return (k);
				k++;
			}
		}
		i++;
	}
	return (-1);
}

// same as get_cmd_arg in exec.c
void	create_cmd_arg(t_mini *mini, int start)
{
	int	i;
	int	j;

	mini->cmd_arg = malloc(sizeof(char *) * (len_cmd_arg(*mini, start) + 1));
	if (!mini->cmd_arg)
		return ;
	i = start;
	j = 0;
	while ((i < mini->type_len) && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == CMD)
		{
			mini->cmd_arg[j] = ft_strdup(mini->token[i]);
			i++;
			j++;
			while ((i < mini->type_len) && (mini->type[i] != PIPE))
			{
				if (mini->type[i] == ARG)
				{
					mini->cmd_arg[j] = ft_strdup(mini->token[i]);
					j++;
				}
				i++;
			}
			//mini->cmd_arg[j] = NULL;
			break ;
		}
		i++;
	}
	mini->cmd_arg[j] = NULL;
}

int	len_cmd_arg(t_mini mini, int start)
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while ((i < mini.type_len) && (mini.type[i] != PIPE))
	{
		if (mini.type[i] == CMD)
		{
			i++;
			count++;
			while ((i < mini.type_len) && (mini.type[i] != PIPE))
			{
				if (mini.type[i] == ARG)
					count++;
				i++;
			}
			break ;
		}
		i++;
	}
	return (count);
}

void	builtin(t_mini *mini, int start)
{
	int	k;
	int	tmp_out;

	tmp_out = dup(STD_OUT);
	if (builtin_files(mini, start) == SUCCESS)
	{
		create_cmd_arg(mini, start);
		if (mini->cmd_arg && mini->cmd_arg[0])
		{
			k = is_builtin(*mini, start);
			if (k == CD)
				mini->exitcode = ft_chd(mini);
			if (k == ECHO)
				mini->exitcode = ft_echo(mini->cmd_arg);
			if (k == ENV)
				mini->exitcode = ft_env(mini, mini->cmd_arg);
			if (k == EXIT)
				mini->exitcode = ft_exit(mini, tmp_out);
			if (k == EXPORT)
				mini->exitcode = ft_export_to_envvars(mini, mini->cmd_arg);
			if (k == PWD)
				mini->exitcode = ft_pwd(mini);
			if (k == UNSET)
				mini->exitcode = ft_unset(mini->cmd_arg, mini);
			double_free((void **)(mini->cmd_arg));
		}
		else
		{
			ft_putstr_fd(ERR_MAL, STD_ERR);
			free_close_exit(mini, EXIT_FAILURE, 0);
		}
	}
	else
		mini->exitcode = 1;
	dup2(tmp_out, STD_OUT);
	close(tmp_out);
}

// res receive 0 from infile, 1 from outfile, -1 on error
int	builtin_files(t_mini *mini, int start)
{
	int	i;
	int	res;

	if (mini->prev_fd0 > 0)
		close(mini->prev_fd0);
	mini->prev_fd0 = dup(mini->fd[0]);
	close(mini->fd[0]);
	i = start;
	res = 0;
	while ((i < mini->type_len) && (mini->type[i] != PIPE))
	{
		if (mini->type[i] == INFILE)
		{
			if (builtin_infile(mini, i) == -1)
				return (close(mini->fd[1]), FAILURE);
		}
		if (mini->type[i] == OUTFILE || mini->type[i] == OUTFAPP)
			res = builtin_outfile(mini, i);
		if (res == -1)
			return (close(mini->fd[1]), FAILURE);
		i++;
	}
	if (res == 1)
	{
		dup2(mini->fd_out, STD_OUT);
		close(mini->fd_out);
	}
	else if (mini->is_pipe == 1)
		dup2(mini->fd[1], STD_OUT);
	close(mini->fd[1]);
	return (SUCCESS);
}

// 0 on success = infile opened (and closed) // -1 on error
int	builtin_infile(t_mini *mini, int i)
{
	char	*tmp;

	if (mini->type[i] == INFILE)
	{
		mini->fd_in = open(mini->token[i], O_RDONLY);
		if (mini->fd_in < 0)
		{
			tmp = ft_strjoin("minishell: ", mini->token[i]);
			perror(tmp);
			free(tmp);
			return (-1);
		}
		close(mini->fd_in);
	}
	return (0);
}

// 1 on success = outfile opened // -1 on error
int	builtin_outfile(t_mini *mini, int i)
{
	char	*tmp;

	// int		is_outfile;
	if (mini->fd_out > 0)
		close(mini->fd_out);
	if (mini->type[i] == OUTFILE)
		mini->fd_out = open(mini->token[i], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (mini->type[i] == OUTFAPP)
		mini->fd_out = open(mini->token[i], O_WRONLY | O_APPEND | O_CREAT,
				0666);
	if (mini->fd_out < 0)
	{
		tmp = ft_strjoin("minishell: ", mini->token[i]);
		perror(tmp);
		free(tmp);
		return (-1);
	}
	return (1);
}

// int	builtin_files(t_mini *mini, int start)
// {
// 	if (mini->prev_fd0 > 0)
// 		close(mini->prev_fd0);
// 	mini->prev_fd0 = dup(mini->fd[0]);
// 	close(mini->fd[0]);
// 	if (builtin_outfile(mini, start) == -1)
// 		return (close(mini->fd[1]), FAILURE);
// 	if (builtin_outfile(mini, start) == 1)
// 	{
// 		dup2(mini->fd_out, STD_OUT);
// 		close(mini->fd_out);
// 	}
// 	else if (mini->is_pipe == 1)
// 		dup2(mini->fd[1], STD_OUT);
// 	close(mini->fd[1]);
// 	return (builtin_infile(mini, start));
// }

// int	builtin_infile(t_mini *mini, int start)
// {
// 	int		i;
// 	char	*tmp;

// 	i = start;
// 	while ((i < mini->type_len) && (mini->type[i] != PIPE))
// 	{
// 		if (mini->type[i] == INFILE)
// 		{
// 			mini->fd_in = open(mini->token[i], O_RDONLY);
// 			if (mini->fd_in < 0)
// 			{
// 				tmp = ft_strjoin("minishell: ", mini->token[i]);
// 				perror(tmp);
// 				free(tmp);
// 				return (FAILURE);
// 			}
// 			close(mini->fd_in);
// 		}
// 		i++;
// 	}
// 	return (SUCCESS);
// }

// int	builtin_outfile(t_mini *mini, int start)
// {
// 	int		i;
// 	int		is_outfile;
// 	char	*tmp;// ft_putnbr_fd(k, STD_ERR);
// printf("k = %d\n", k);

// 	i = start;
// 	is_outfile = 0;
// 	while ((i < mini->type_len) && (mini->type[i] != PIPE))
// 	{
// 		if (mini->type[i] == OUTFILE || mini->type[i] == OUTFAPP)
// 		{
// 			if (mini->fd_out > 0)
// 				close(mini->fd_out);
// 			is_outfile = 1;
// 			if (mini->type[i] == OUTFILE)
// 				mini->fd_out = open(mini->token[i],
// 						O_// ft_putnbr_fd(k, STD_ERR);
// printf("k = %d\n", k);WRONLY | O_TRUNC | O_CREAT, 0666);
// 			if (mini->type[i] == OUTFAPP)
// 				mini->fd_out = open(mini->token[i],
// 						O_WRONLY | O_APPEND | O_CREAT, 0666);
// 			if (mini->fd_out < 0)
// 			{
// 				tmp = ft_strjoin("minishell: ", mini->token[i]);
// 				perror(tmp);
// 				free(tmp);
// 				return (-1);
// 			}
// 		}
// 		i++;
// 	}
// 	return (is_outfile);
// }

/*** draft   */

// printf("cmd_arg:");
// while (mini->cmd_arg[i])
// {
// 	printf("%s / ", mini->cmd_arg[i]);
// 	i++;
// }
// printf("\n");

// //
// int i = 0;
// printf("cmd_arg:");
// while (mini->cmd_arg[i])
// {
// 	printf("%s / ", mini->cmd_arg[i]);
// 	i++;
// }
// printf("\n");
// //
//
// 	int j = 0;
// ft_putstr_fd("cmd_arg:", 2);
// ft_putstr_fd("\n", 2);
// while (mini->cmd_arg[j])
// {
// 	ft_putstr_fd(mini->cmd_arg[j], 2);
// 	ft_putstr_fd("\n", 2);
// 	j++;
// }
// ft_putstr_fd("\n", 2);
//