/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:56:00 by caguillo          #+#    #+#             */
/*   Updated: 2024/04/18 03:34:55 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include "../libft/libft.h"
// # include <asm-generic/fcntl.h>
// # include <bits/fcntl-linux.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2
// # define WH_HEREDOC 1
// # define NO_HEREDOC 0
# define ERR_RDL "minishell: readline: Can't read input\n"
# define ERR_STX "minishell: Syntax error\n"
# define ERR_SQX "minishell: Syntax error (quote opened)\n"
# define ERR_DQX "minishell: Syntax error (dquote opened)\n"
# define ERR_GNL "minishell: gnl: Can't read input\n"
# define ERR_MAL "minishell: Malloc failed\n"
# define ERR_CMD ": Command not found\n"
# define ERR_ACX ": Permission denied\n"
# define ERR_DIR ": No such file or directory\n"
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_STX 2
# define EXIT_NOCMD 127
# define EXIT_DENIED 126
# define EXIT_NODIR 127

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
	char *fprompt; // to be free'd
	char **token;  // to be free'd
	t_type *type;  // to be free'd
	int		type_len;
	int		exitcode;
	//
	char **cmd_arg; // to be free'd
	char **paths;   // to be free'd
	char	**envvars;
	//
	int fd_in;    // to be closed
	int fd_out;   // to be closed
	int fd[2];    // to be closed
	int prev_fd0; // to be closed
	int		is_pipe;
	//
	pid_t	last_pid;
	int		status;
	int		is_last_pid;
	//
	int		is_heredoc;
	int		hd_pos;
	char	*lim;
	// int hd_fd[1024]; // to be closed
	char	*hd_name[1024];
	int		hd_idx;
	int hd_fd; // to be closed
}			t_mini;

// check_quote.c
int			check_quotes(char *str);
int			check_quotes_output(int s_open, int d_open);
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
// format_prompt_utils2.c
void		quote_in_len_minus(char *prompt, int *i, int *len, int q);
void		space_in_len_minus(char *prompt, int *i);
void		squote_in_get_minus(char *tmp_prompt, char *prompt, int *i, int *j);
void		dquote_in_get_minus(char *tmp_prompt, char *prompt, int *i, int *j);
void		space_in_get_minus(char *prompt, int *j);
// format_prompt_utils3.c
void		other_in_get_minus(char *tmp_prompt, char *prompt, int *i, int *j);
void		quote_in_len_plus(char *prompt, int *i, int *len, int q);
void		symbol_in_len_plus(char *prompt, int *i, int *len);
void		squote_in_get_plus(char *f_prompt, char *prompt, int *i, int *j);
void		dquote_in_get_plus(char *f_prompt, char *prompt, int *i, int *j);
// format_prompt_utils4.c
void		symbol_in_get_plus(char *f_prompt, char *prompt, int *i, int *j);
void		other_in_get_plus(char *f_prompt, char *prompt, int *i, int *j);

// tokenizer
int			blocks_counter(char *fprompt);
char		**token_init(char **token, char *fprompt);
int			is_sep(char c);
int			is_in_quotes(char *prompt, int i);
void		tokenizer(t_mini *mini);

// type.c
t_type		*create_type(t_mini *mini);
t_type		get_type(char **token, int i);
t_type		get_type2(char **token, int i);
void		check_type(t_type *type, char **token);
int			ft_tabstr_len(char **tab);

// to_exec.c
int			nbr_cmd(t_mini mini);
void		re_init_mini(t_mini *mini);
void		close_prev_pipe(t_mini mini);
void		blocks_to_child(t_mini *mini, char **envp, int nbr_cmd);
void		get_heredoc(t_mini *mini, int start);
int			is_infile(t_mini *mini, int start);
void		open_infile(t_mini *mini, char *infile);
int			is_outfile(t_mini *mini, int start);
void		child(t_mini *mini, char **envp, int start);

// exec.c
int			check_slash(char *str);
void		exec_arg(t_mini mini, char **envp, int start);
void		get_cmd_arg(t_mini *mini, int start);
void		exec_cmd(t_mini mini, char **envp);
void		exec_abs(t_mini mini, char **envp);

// free_close_exit.c
void		close_exit(t_mini mini, int k);
void		perror_close_exit(char *err, t_mini mini, int k);
void		perror_open(t_mini mini, char *filename);
void		free_close_exit(t_mini *mini, int exit_code, int is_paths);
void		putstr_error(char *cmd0, char *err_str);

// heredoc.c
void		open_heredoc(t_mini *mini);
void		fill_heredoc(t_mini *mini, int fd);
void		limiter_err_mal(t_mini mini);

// path.c
void		get_paths(t_mini *mini, char **envp);
void		slash_paths(t_mini *mini);
int			check_in_str(char *s1, char *s2);
char		*check_path(char **paths, char **cmd);

/***************temp temp temp *****************/

// ft_split.c
char		**ft_split(char const *s, char c);

// temp.c
void		temp_display_tabs(char **token, t_type *type);
// size_t		ft_tabint_len(int *tab);
// size_t		ft_tabtype_len(t_type *tab);

// syntax checks
char		get_next_char(char *prompt, int i);
int			check_pipes(char *prompt);
int			syntax_checker(char *prompt);

#endif
