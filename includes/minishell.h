/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:56:00 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/03 20:52:17 by aether           ###   ########.fr       */
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
# include "../libft/libft.h"
# include <errno.h>

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2
# define ERR_RDL "minishell: can't read input\n"
# define ERR_STX "minishell: syntax error\n"
# define ERR_SQX "minishell: syntax error (quote opened)\n"
# define ERR_DQX "minishell: syntax error (dquote opened)\n"
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_STX 2

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

// format_prompt.c
char		*format_prompt(char *prompt);
int			len_prompt_minus_space(char *prompt);
char		*get_prompt_minus_space(char *prompt);
int			len_prompt_plus_space(char *prompt);
char		*get_prompt_plus_space(char *prompt);

// format_prompt_utils.c
int			is_space(char c);
int			is_symbol(char c);
int			is_quote(char c);
int			check_after_symbol(char *prompt, int i);
int			check_before_symbol(char *prompt, int i);

// type.c
t_type		*create_type(char **token);
t_type		get_type(char **token, int i);
t_type		get_type2(char **token, int i);
void		check_type(t_type *type, char **token);
size_t		ft_tabstr_len(char **tab);

// ft_split.c
char		**ft_split(char const *s, char c);

// check_quote.c
int			check_quotes(char *str);
int			check_quotes_output(int s_open, int d_open);

// temp.c
void		temp_display_tabs(char **token, t_type *type);
// size_t		ft_tabint_len(int *tab);
// size_t		ft_tabtype_len(t_type *tab);

int         is_in_quotes(char *prompt, int i);
int         is_sep(char c);

#endif
