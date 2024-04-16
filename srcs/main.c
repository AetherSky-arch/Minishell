/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:55:50 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/16 21:57:23 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quit(char *prompt)
{
	free(prompt);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

void	wait_exitcode(t_mini *mini)
{
	while (errno != ECHILD)
	{
		if (wait(&((*mini).status)) == (*mini).last_pid)
		{
			if (WIFEXITED((*mini).status))
				(*mini).exitcode = WEXITSTATUS((*mini).status);
		}
	}
}

void	read_prompt(t_mini *mini)
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
		mini->exitcode = check_quotes(prompt);
		if (mini->exitcode != 0)
			return (free(prompt));
		if (syntax_checker(prompt) == 0)
		{
			ft_putstr_fd(ERR_STX, STD_ERR);
			mini->exitcode = EXIT_STX;
			return (free(prompt));
		}
		if (mini->exitcode == 0)
		{
			mini->fprompt = format_prompt(prompt);
			free(prompt);
			mini->token = ft_split(mini->fprompt, ' ');
			// tokenizer(mini);
			mini->type = create_type(mini);
			check_type(mini->type, mini->token);
			/*** syntax_error of type succesion ? ***/
			/***  temp: for checking  ***/
			printf("f_prompt:%s\n", mini->fprompt);
			temp_display_tabs(mini->token, mini->type);
		}
	}
	else
	{
		ft_putstr_fd(ERR_RDL, STD_ERR);
		mini->exitcode = EXIT_FAILURE;
		free(prompt);
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	(void)envp;
	mini = (t_mini){0}; // ok?
    // mini.envvars = double_dup(envp);
    // if (mini.envvars == NULL)
    // {
    //     return (1);
    // }
	if (isatty(STD_IN))
	{
		while (1)
		{
			mini = (t_mini){0};
			//re_init_mini(&mini);
			read_prompt(&mini);
			open_heredoc(&mini);
			
			blocks_to_child(&mini, envp, nbr_cmd(mini));
			// blocks_to_child(&mini, envp, nbr_cmd(mini), NO_HEREDOC);
			close_prev_pipe(mini);
			wait_exitcode(&mini);
			//
			/*** free here for now ***/
			if (mini.exitcode != EXIT_STX)
			{
				double_free((void **)mini.token);
				free(mini.fprompt);
				free(mini.type);
			}
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
}
