/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:55:50 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/06 14:58:30 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_exitcode;

void	quit(t_mini *mini, char *prompt, int k)
{
	free(prompt);
	rl_clear_history();
    double_free((void **)mini->envvars);
	ft_putstr_fd("exit\n", STD_OUT);
	exit(k);
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

int	read_prompt(t_mini *mini, int prev_exit, char **envp)
{
	char	*prompt;

	prompt = readline("~$ ");
	// prompt = get_next_line(STD_IN);
	if (g_exitcode == 130)
		prev_exit = 130;
	if (prompt)
	{
		// if (ft_strcmp(prompt, "exit\n") == 0)
		add_history(prompt);
		if (ft_strcmp(prompt, "exit") == 0)
			quit(mini, prompt, prev_exit);
		if (ft_strcmp(prompt, "\n") == 0)
			return (mini->exitcode = prev_exit, free(prompt), FAILURE);
		mini->exitcode = check_quotes(prompt);
		if (mini->exitcode != 0)
			return (free(prompt), FAILURE);
		//
		mini->envvars = double_dup(envp);
		if (mini->envvars == NULL)
			return (free(prompt), FAILURE);
		//
		mini->fprompt = format_prompt(prompt);
		free(prompt);
		mini->token = split_fprompt(mini->fprompt, ' ');
		envvars_manager(mini->token, mini);
		mini->type = create_type(mini);
		check_type(mini);
		check_quoted_type(mini->type, mini->token);
		//
		/***  temp: for checking  ***/
		printf("f_prompt:%s\n", mini->fprompt);
		temp_display_tabs(mini->token, mini->type);
	}
	else
		quit(mini, prompt, prev_exit);
	return (SUCCESS);
}

// check_syntax return: 1 on failure (error), 0 on success (no error)
int	check_syntax(t_mini *mini)
{
	char	*tmp;

	if (check_type_sequence(mini) == FAILURE)
		return (FAILURE);
	if (syntax_checker(mini) == FAILURE)
	{
		if (mini->token[mini->stx_err_idx])
		{
			tmp = ft_strjoin(ERR_HDX, mini->token[mini->stx_err_idx]);
			ft_putstr_fd(tmp, STD_ERR);
			ft_putstr_fd("\n", STD_ERR);
			free(tmp);
		}
		else
			ft_putstr_fd(ERR_STX, STD_ERR);
		mini->exitcode = EXIT_STX;
		return (FAILURE);
	}
	return (check_heredoc(mini));
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	int		prev_exit;
    char    **envvars;

	(void)argc;
	(void)argv;
	(void)envp;
	prev_exit = 0;
	g_exitcode = 0;
	envvars = double_dup(envp);
	if (envvars == NULL)
		return (1);
	while (1)
	{
		mini = (t_mini){0};
        mini.envvars = envvars;
		manage_signal();
		if (read_prompt(&mini, prev_exit, envp) == SUCCESS)
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
			/*** free here for now ***/
			double_free((void **)mini.token);
			double_free((void **)mini.envvars);
			free(mini.fprompt);
			free(mini.type);
		}
		if (g_exitcode == 130)
			mini.exitcode = 130;
		prev_exit = mini.exitcode;
		printf("exitcode:%d\n", mini.exitcode);
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
	/***never returned ? ***/
}
