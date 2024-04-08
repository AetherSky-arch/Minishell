/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:55:50 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/08 19:14:42 by aether           ###   ########.fr       */
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
		if (wait(&((*mini).status)) == (*mini).pid)
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
	if (prompt)
	{
		add_history(prompt);
		if (ft_strcmp(prompt, "exit") == 0)
			quit(prompt);
		mini->exitcode = check_quotes(prompt);
		// if (syntax_checker(prompt) == 0)
        // {
        //     ft_putstr_fd("syntax error\n", 2);
        //     return ;
        // }
		if (mini->exitcode == 0)
		{
			mini->fprompt = format_prompt(prompt);
			free(prompt);
			mini->token = ft_split(mini->fprompt, ' ');
			// tokenizer(mini);
			mini->type = create_type(mini->token);
			check_type(mini->type, mini->token);
			// syntax_error of type succesion
			// temp: for checking
			printf("f_prompt =%s\n", mini->fprompt);
			temp_display_tabs(mini->token, mini->type);			
			// // free here for now
			// double_free((void **)mini->token);
			// free(mini->fprompt);
			// free(mini->type);

		}
	}
	else
	{
		ft_putstr_fd(ERR_RDL, STD_ERR);
		mini->exitcode = EXIT_FAILURE;
	}
}



int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;	
	(void)envp;	
	mini = (t_mini){0};
	if (isatty(STD_IN))
	{
		while (1)
		{
			read_prompt(&mini);
			// block_to_child(&mini, envp);
			// // wait_exitcode(&mini);
			// waitpid(-1, &(mini.status), 0); 
			// free here for now
			double_free((void **)mini.token);
			free(mini.fprompt);
			free(mini.type);
		}
	}
	else
	{
		if (errno != ENOTTY)
		{
			// to execute a script ?
		}
		else
			perror("minishell: tty");
	}
	rl_clear_history();
	return (mini.exitcode);
}
