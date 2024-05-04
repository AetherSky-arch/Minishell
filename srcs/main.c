/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:55:50 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/04 21:44:02 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quit(char *prompt)
{
	free(prompt);
	rl_clear_history();
	ft_putstr_fd("exit\n", STD_OUT);
	exit(EXIT_SUCCESS);
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
	if (prompt)
	{
		// if (ft_strcmp(prompt, "exit\n") == 0)
		add_history(prompt);
		if (ft_strcmp(prompt, "exit") == 0)
			quit(prompt);
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
	{
		// if (prompt == EOF)
		quit(prompt);
		// ft_putstr_fd(ERR_RDL, STD_ERR);
		// mini->exitcode = EXIT_FAILURE;
		// free(prompt);
		// rl_clear_history();
		// exit(EXIT_FAILURE);
	}
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

	(void)argc;
	(void)argv;
	(void)envp;
	prev_exit = 0;
	if (isatty(STD_IN))
	{
		while (1)
		{
			mini = (t_mini){0};
			//
			// mini.envvars = double_dup(envp);
			// if (mini.envvars == NULL)
			// 	return (1);
			//
			signal_handler();
			if (read_prompt(&mini, prev_exit, envp) == SUCCESS)
			{
				if (check_syntax(&mini) == FAILURE)
					open_heredoc(&mini, nbr_heredoc(mini));
				else
				{
					open_heredoc(&mini, nbr_heredoc(mini));
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
			prev_exit = mini.exitcode;
			printf("exitcode:%d\n", mini.exitcode);
		}
	}
	else
	{
		if (errno != ENOTTY)
		{
			/*** to execute a script ? ***/
		}
		else
			perror("minishell: tty");
	}
	rl_clear_history();
	return (mini.exitcode);
	/***never returned ? ***/
}
