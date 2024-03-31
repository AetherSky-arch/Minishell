/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:56:00 by caguillo          #+#    #+#             */
/*   Updated: 2024/03/31 23:55:24 by caguillo         ###   ########.fr       */
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

typedef enum e_type
{
	INFILE,
	OUTFILE,
	OUTFAPP,
	GREAT,
	DGREAT,
	LESS,
	HEREDOC,
	LIMITER,
	PIPE,
	CMD,
	ARG
}			t_type;

typedef struct s_mini
{
	char	*fprompt;
	char	**token;
	t_type	*type;
	int		exitcode;
}			t_mini;

// main.c
void		read_prompt(t_mini *mini);

// temp.c
void		temp_display_tabs(char **token, t_type *type);
size_t		temp_ft_tablen2(t_type *tab);

// format_prompt.c
char		*format_prompt(char *prompt);
int			len_prompt_minus_space(char *prompt);
char		*get_prompt_minus_space(char *prompt);
int			len_prompt_plus_space(char *prompt);
char		*get_prompt_plus_space(char *prompt);

// type.c
t_type		*create_type(char **token);
t_type		get_type(char **token, int i);
t_type		get_type2(char **token, int i);
size_t		ft_tablen(char **tab);

// libft.c
void		ft_putstr_fd(char *str, int fd);
size_t		ft_strlen(char *str);
int			ft_strcmp(char *s1, char *s2);

// ft_split.c
char		**ft_split(char const *s, char c);

// format_prompt_tools1.c
int			is_space(char c);
int			is_symbol(char c);
int			is_quote(char c);
int			check_after_symbol(char *prompt, int i);
int			check_before_symbol(char *prompt, int i);

#endif