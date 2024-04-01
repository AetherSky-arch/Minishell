/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:55:50 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/02 00:22:36 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	(void)envp;
	mini = (t_mini){0};
	if (isatty(STDIN))
	{
		while (1)
		{
			read_prompt(&mini);
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
	// return(exitcode);
	return (0);
}

void	read_prompt(t_mini *mini)
{
	char	*prompt;

	prompt = readline("~$ ");
	if (prompt)
	{
		add_history(prompt);
		(*mini).fprompt = format_prompt(prompt);
		free(prompt);
		(*mini).token = ft_split((*mini).fprompt, ' ');
		(*mini).type = create_type((*mini).token);
		check_type((*mini).type, (*mini).token);
		// temp for checking
		printf("%s\n", (*mini).fprompt);
		temp_display_tabs((*mini).token, (*mini).type);
		// free here for now
		free_tabstr((*mini).token);
		free((*mini).fprompt);
		free((*mini).type);
	}
	else
	{
		ft_putstr_fd(ERR_RDL, 2);
		(*mini).exitcode = EXIT_FAILURE;
	}
}

// if (syntax_error(prompt) == 0)
// 		{
// 		}
// 		else
// 		{
// 			ft_putstr_fd(ERR_STX, 2);
// 			(*mini).exitcode = EXIT_STX;
// 		}