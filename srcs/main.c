/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:55:50 by caguillo          #+#    #+#             */
/*   Updated: 2024/03/30 00:25:33 by caguillo         ###   ########.fr       */
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
		format_prompt(mini, prompt);
		free(prompt);
	}
	else
	{
		ft_putstr_fd(ERR_RDL, 2);
		(*mini).exitcode = EXIT_FAILURE;
	}
}

void	format_prompt(t_mini *mini, char *prompt)
{
	int	i;
	int	nbr;

	if (!(prompt))
		return ;
	i = 0;
	while (prompt[i])
	{
		if (is_symbol(prompt[i]) == 1)
		{
			//...
		}
		i++;
	}
}

int	is_symbol(char c)
{
	// < > |
}