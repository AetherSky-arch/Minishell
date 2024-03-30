/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:56:00 by caguillo          #+#    #+#             */
/*   Updated: 2024/03/30 23:45:38 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// malloc, free
# include <stdlib.h>
// isatty, write
# include <unistd.h>
// readline
# include <readline/history.h>
# include <readline/readline.h>
// printf
# include <stdio.h>
// errno
# include <errno.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define ERR_RDL "minishell: Can't read input\n"
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_mini
{
	char	*fprompt;
	char	**token;
	char	**type;
	int		exitcode;
}			t_mini;

// main.c
void		read_prompt(t_mini *mini);

// format_prompt.c
char		*format_prompt(char *prompt);
int			len_prompt_minus_space(char *prompt);
char		*get_prompt_minus_space(char *prompt);
int			len_prompt_plus_space(char *prompt);
char		*get_prompt_plus_space(char *prompt);

// libft.c
void		ft_putstr_fd(char *str, int fd);
size_t		ft_strlen(char *str);

// ft_split.c
char		**ft_split(char const *s, char c);

// format_prompt_tools1.c
int			is_space(char c);
int			is_symbol(char c);
int			is_quote(char c);
int			check_after_symbol(char *prompt, int i);
int			check_before_symbol(char *prompt, int i);

#endif