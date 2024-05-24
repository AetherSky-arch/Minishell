/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:55:50 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/24 03:18:07 by aether           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_exitcode;

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	int		prev_exit;
	char	**envvars;

	(void)argc;
	(void)argv;
	main_init_utils(&prev_exit, &g_exitcode);
	envvars = double_dup(envp);
	if (envvars == NULL)
		return (EXIT_FAILURE);
	while (1)
	{
		mini = (t_mini){0};
		mini.envvars = double_dup(envvars);
		mini.lastcode = prev_exit;
		(double_free((void **)envvars), manage_signal());
		if (read_prompt(&mini) == SUCCESS)
			mini_shell(&mini);
		envvars = double_dup(mini.envvars);
		double_free((void **)mini.envvars);
		if (g_exitcode == 130)
			mini.exitcode = 130;
		prev_exit = mini.exitcode;
	}
	return (rl_clear_history(), mini.exitcode);
}

void	mini_shell(t_mini *mini)
{
	g_exitcode = 0;
	if (check_syntax(mini) == FAILURE)
		open_heredoc(mini, nbr_heredoc(*mini));
	else
	{
		open_heredoc(mini, nbr_heredoc(*mini));
		if (g_exitcode != 130)
			blocks_to_exec(mini, mini->envvars, nbr_block(*mini));
		close_prev_pipe(*mini);
		wait_exitcode(mini);
	}
	unlink_free_hdname(mini);
	double_free((void **)mini->token);
	free(mini->fprompt);
	free(mini->type);
}

int	read_prompt(t_mini *mini)
{
	char	*prompt;

	prompt = readline("~$ ");
	if (g_exitcode == 130)
		mini->lastcode = 130;
	if (prompt)
	{
		add_history(prompt);
		if (ft_strcmp(prompt, "exit") == 0)
			quit(mini, prompt, mini->lastcode);
		if (ft_strcmp(prompt, "") == 0)
			return (mini->exitcode = mini->lastcode, free(prompt), FAILURE);
		mini->exitcode = check_quotes(prompt);
		if (mini->exitcode != 0)
			return (free(prompt), FAILURE);
		mini->fprompt = format_prompt(prompt);
		free(prompt);
		mini->token = split_fprompt(mini->fprompt, ' ');
		read_prompt_next(mini);
	}
	else
		quit(mini, prompt, mini->lastcode);
	return (SUCCESS);
}

void	read_prompt_next(t_mini *mini)
{
	if (mini->token)
		check_dollar(mini);
	mini->type = create_type(mini);
	check_type(mini);
	check_quoted_type(mini->type, mini->token);
	update_env(mini);
}

void	quit(t_mini *mini, char *prompt, int k)
{
	free(prompt);
	double_free((void **)mini->envvars);
	rl_clear_history();
	ft_putstr_fd("exit\n", STD_OUT);
	exit(k);
}

/*** draft GNL ***/
// prompt = get_next_line(STD_IN);
// if (ft_strcmp(prompt, "exit\n") == 0) //gnl
// if (ft_strcmp(prompt, "\n") == 0) //gnl

/***  temp: for checking  ***/
// printf("f_prompt:%s\n", mini->fprompt);
// temp_display_tabs(mini->token, mini->type);
