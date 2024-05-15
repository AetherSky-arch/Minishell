/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:55:50 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/15 21:42:39 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_exitcode;

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	int		prev_exit;
	char	**envvars;
	char	*c_cmd;

	if (argc == 3 && ft_strcmp("-c", argv[1]) == 0 && argv[2])
		c_cmd = argv[2];
	else
		c_cmd = NULL;
	prev_exit = 0;
	g_exitcode = 0;
	envvars = double_dup(envp);
	if (envvars == NULL)
		return (EXIT_FAILURE);
	while (1)
	{
		mini = (t_mini){0};
		mini.envvars = double_dup(envvars);
		mini.lastcode = prev_exit;
		double_free((void **)envvars);
		manage_signal();
		if (read_prompt(&mini, c_cmd) == SUCCESS)
		{
			g_exitcode = 0; // initi for open_heredoc
			if (check_syntax(&mini) == FAILURE)
				open_heredoc(&mini, nbr_heredoc(mini));
			else
			{
				open_heredoc(&mini, nbr_heredoc(mini));
				if (g_exitcode != 130)
					blocks_to_exec(&mini, envp, nbr_block(mini));
				close_prev_pipe(mini);
				wait_exitcode(&mini);
			}
			unlink_free_hdname(&mini);
			double_free((void **)mini.token);
			free(mini.fprompt);
			free(mini.type);
		}
		envvars = double_dup(mini.envvars);
		double_free((void **)mini.envvars);
		if (g_exitcode == 130)
			mini.exitcode = 130;
		prev_exit = mini.exitcode;
		// printf("exitcode:%d\n", mini.exitcode);
		if (c_cmd)
			break ;
	}
	// if (isatty(STD_IN))
	// {
	// }
	// else
	// {
	// 	if (errno != ENOTTY)
	// 	{
	// 		/*** to execute a script ? ***/
	// 	}
	// 	else
	// 		perror("minishell: tty");
	// }
	rl_clear_history();
	return (mini.exitcode);
}

int	read_prompt(t_mini *mini, char *c_cmd)
{
	char	*prompt;

	if (c_cmd)
		prompt = ft_strdup(c_cmd);
	else
		prompt = readline("~$ ");
	// prompt = get_next_line(STD_IN);
	if (g_exitcode == 130)
		mini->lastcode = 130;
	if (prompt)
	{
		// if (ft_strcmp(prompt, "exit\n") == 0) //gnl
		add_history(prompt);
		if (ft_strcmp(prompt, "exit") == 0)
			quit(mini, prompt, mini->lastcode);
		// if (ft_strcmp(prompt, "\n") == 0) //gnl
		if (ft_strcmp(prompt, "") == 0)
			return (mini->exitcode = mini->lastcode, free(prompt), FAILURE);
		mini->exitcode = check_quotes(prompt);
		if (mini->exitcode != 0)
			return (free(prompt), FAILURE);
		mini->fprompt = format_prompt(prompt);
		free(prompt);
		mini->token = split_fprompt(mini->fprompt, ' ');
		envvars_manager(mini->token, mini);
		mini->type = create_type(mini);
		check_type(mini);
		check_quoted_type(mini->type, mini->token);
		/***  temp: for checking  ***/
		// printf("f_prompt:%s\n", mini->fprompt);
		// temp_display_tabs(mini->token, mini->type);
	}
	else
		quit(mini, prompt, mini->lastcode);
	return (SUCCESS);
}

void	wait_exitcode(t_mini *mini)
{
	pid_t	tmp;

	// while (errno != ECHILD)
	while (1)
	{
		tmp = wait(&((*mini).status));
		if (tmp == -1)
			break ;
		if (tmp == (*mini).last_pid)
		{
			if (WIFEXITED((*mini).status))
			{
				(*mini).exitcode = WEXITSTATUS((*mini).status);
				// printf("wait exitcode:%d\n", mini->exitcode);
				break ;
			}
		}
	}
}

void	quit(t_mini *mini, char *prompt, int k)
{
	free(prompt);
	double_free((void **)mini->envvars);
	rl_clear_history();
	ft_putstr_fd("exit\n", STD_OUT);
	exit(k);
}
