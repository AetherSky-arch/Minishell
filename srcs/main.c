/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:55:50 by caguillo          #+#    #+#             */
/*   Updated: 2024/03/30 23:20:11 by caguillo         ###   ########.fr       */
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
		// display_prompt();
		while(1)
			read_prompt(&mini);
		// format_prompt();
		// split_prompt();
		// get_type()
	}
	else
	{
		if (errno != ENOTTY)
		{
			// to execute a script
		}
		else
			perror("minishell: tty");
	}
	// return(exitcode);
	return (0);
}

void	read_prompt(t_mini *mini)
{
	char	*prompt;

	prompt = readline(">");
	if (prompt)
	{
		(*mini).fprompt = format_prompt(prompt);
		// update prompt history
		free(prompt);
		printf("%s\n", (*mini).fprompt);
		free((*mini).fprompt);
	}
	else
	{
		ft_putstr_fd(ERR_RDL, 2);
		(*mini).exitcode = EXIT_FAILURE;
	}
}
