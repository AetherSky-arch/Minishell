/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:55:50 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/01 01:40:26 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quit(char *prompt)
{
	free(prompt);
	//rl_clear_history();
	exit(EXIT_SUCCESS);
}

void	wait_exitcode(t_mini *mini)
{
	while (errno != ECHILD)
	{
		//printf("ici");
		if (wait(&((*mini).status)) == (*mini).last_pid)
		{
			if (WIFEXITED((*mini).status))
			{
				(*mini).exitcode = WEXITSTATUS((*mini).status);
				//printf("wait exitcode:%d\n", mini->exitcode);
			}	
		}
	}
	
}

int	read_prompt(t_mini *mini)
{
	char	*prompt;

	//prompt = readline("~$ ");
	prompt = get_next_line(STD_IN);
	if (prompt)
	{
		if (ft_strcmp(prompt, "exit\n") == 0)
		// add_history(prompt);
		// if (ft_strcmp(prompt, "exit") == 0)
			quit(prompt);
		mini->exitcode = check_quotes(prompt);
		if (mini->exitcode != 0)
			return (free(prompt), FAILURE);
		mini->fprompt = format_prompt(prompt);
		free(prompt);
		mini->token = split_fprompt(mini->fprompt, ' ');		
		mini->type = create_type(mini);
		// check_type(mini->type, mini->token); --> for which case ???
		check_quoted_type(mini->type, mini->token);
		//		
		/***  temp: for checking  ***/
		printf("f_prompt:%s\n", mini->fprompt);
		temp_display_tabs(mini->token, mini->type);
		return (SUCCESS);
	}
	else
	{
		ft_putstr_fd(ERR_RDL, STD_ERR);
		mini->exitcode = EXIT_FAILURE;
		free(prompt);
		//rl_clear_history();
		exit(EXIT_FAILURE);
	}
}

// check_syntax return: 1 on failure (error), 0 on success (no error)
int	check_syntax(t_mini *mini)
{
	char	*tmp;

	if (check_type_sequence(mini) == FAILURE)
		return(FAILURE);
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

	(void)argc;
	(void)argv;
	(void)envp;
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
			if (read_prompt(&mini) == SUCCESS)
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
	// rl_clear_history();
	return (mini.exitcode);
	/***never returned ? ***/
}
