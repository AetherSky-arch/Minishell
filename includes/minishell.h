/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:56:00 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/14 21:27:25 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
// # include <asm-generic/fcntl.h>
// # include <bits/fcntl-linux.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// # define _GNU_SOURCE
# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2
# define ERR_RDL "minishell: readline: Can't read input\n"
# define ERR_STX "minishell: syntax error\n"
# define ERR_SQX "minishell: syntax error (squote opened)\n"
# define ERR_DQX "minishell: syntax error (dquote opened)\n"
# define ERR_HDX "minishell: syntax error near unexpected token `"
# define ERR_GNL "minishell: gnl: Can't read input\n"
# define ERR_MAL "minishell: malloc failed\n"
# define ERR_NHD "minishell: maximum here-document count exceeded\n"
# define ERR_CMD ": command not found\n"
# define ERR_ACX ": Permission denied\n"
# define ERR_DIR ": No such file or directory\n"
# define ERR_ISD ": Is a directory\n"
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_STX 2
# define EXIT_NOCMD 127
# define EXIT_DENIED 126
# define EXIT_NODIR 127
# define EXIT_SIGINT 130
# define SUCCESS 0
# define FAILURE 1
# define TRUE 1
# define FALSE 0

extern int	g_exitcode;

typedef enum e_built
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET
}			t_built;

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
	// prompt
	char *fprompt; // to be free'd
	char **token;  // to be free'd
	t_type *type;  // to be free'd
	int		type_len;
	int		stx_err_idx;
	// exec
	char **cmd_arg; // to be free'd
	char **paths;   // to be free'd
	char **envvars; // to be free'd
	// file descriptor
	int fd_in;    // to be closed
	int fd_out;   // to be closed
	int fd[2];    // to be closed
	int prev_fd0; // to be closed
	int		is_pipe;
	// fork/wait
	pid_t	last_pid;
	int		status;
	int		is_last_pid;
	int		exitcode;
	int		lastcode;
	// heredoc
	int		is_heredoc;
	int		hd_pos;
	int		hd_idx;
	char	*lim;
	int hd_fd;      // to be closedecho hi | > >>
	char **hd_name; // to be free'd
}			t_mini;

// main.c
int			read_prompt(t_mini *mini, char *c_cmd);
void		wait_exitcode(t_mini *mini);
void		quit(t_mini *mini, char *prompt, int k);

// check_quote.c
int			check_quotes(char *str);
int			check_quotes_output(int s_open, int d_open);
void		check_quoted_type(t_type *type, char **token);
int			inside_quotes(char const *str, int i);
char		*remove_quote(char *str);

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
void		squote_in_get_plus2(char *f_prompt, char *prompt, int *i, int *j);

// format_prompt_utils4.c
void		dquote_in_get_plus(char *f_prompt, char *prompt, int *i, int *j);
void		dquote_in_get_plus2(char *f_prompt, char *prompt, int *i, int *j);
void		symbol_in_get_plus(char *f_prompt, char *prompt, int *i, int *j);
void		other_in_get_plus(char *f_prompt, char *prompt, int *i, int *j);

// split_fprompt.c
char		**split_fprompt(char const *s, char c);

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
void		check_type(t_mini *mini);
void		check_type_block(t_mini *mini, int start);
int			get_cmd_idx(t_mini mini, int start);
int			ft_tabstr_len(char **tab);

// syntax_checker.c
int			check_syntax(t_mini *mini);
int			check_pipe(t_mini *mini);
int			check_type_sequence(t_mini *mini);

// heredoc_setting.c
void		open_heredoc(t_mini *mini, int nbr_hd);
char		**create_hd_name(t_mini *mini);
char		*heredoc_name(void);
void		fill_heredoc(t_mini *mini, int fd);
void		limiter_err_mal(t_mini mini);

// files.c
int			is_infile(t_mini *mini, int start);
void		open_infile(t_mini *mini, char *infile);
int			is_outfile(t_mini *mini, int start);
void		check_files(t_mini *mini, int start);

// heredoc_to_exec.c
int			nbr_heredoc(t_mini mini);
void		get_heredoc(t_mini *mini, int start);
int			get_heredoc_idx(t_mini *mini, int hd_pos);
void		unlink_free_hdname(t_mini *mini);
int			check_heredoc(t_mini *mini);

// to_exec.c
int			nbr_block(t_mini mini);
void		blocks_to_exec(t_mini *mini, char **envp, int nbr_block);
void		child(t_mini *mini, char **envp, int start);
void		close_prev_pipe(t_mini mini);

// path.c
void		get_paths(t_mini *mini, char **envp);
void		slash_paths(t_mini *mini);
int			check_in_str(char *s1, char *s2);
char		*check_path(char **paths, char **cmd);

// exec.c
int			check_slash(char *str);
void		exec_arg(t_mini mini, char **envp, int start);
void		get_cmd_arg(t_mini *mini, int start);
void		exec_cmd(t_mini mini, char **envp);
void		exec_abs(t_mini mini, char **envp);
void		is_a_directory(t_mini *mini, char *is_cmd_or_dir);

// buitins.c
int			is_builtin(t_mini mini, int start);
void		create_cmd_arg(t_mini *mini, int start);
int			len_cmd_arg(t_mini mini, int start);
void		builtin(t_mini *mini, int start);
int			builtin_files(t_mini *mini, int start);
int			builtin_infile(t_mini *mini, int i);
int			builtin_outfile(t_mini *mini, int i);

// free_close_exit.c
void		close_exit(t_mini mini, int k);
void		perror_close_exit(char *err, t_mini *mini, int k);
void		perror_open_free(t_mini *mini, char *filename);
void		free_close_exit(t_mini *mini, int exit_code, int is_paths);
void		putstr_error(char *cmd0, char *err_str);

// signal.c
void		manage_signal(void);
void		handle_sigint(int signal);
void		handle_sigint_in_child(int signal);
void		handle_sigint_in_hd(int signal);

// envvars ($)
void		envvars_manager(char **tokens, t_mini *mini, int prev_exit);

//--------------------- BUILTINS ------------------------------------//

// echo.c --> to be secured
int			ft_echo(char **args);

// chd.c
int			checkfor_dir(t_mini *mini, char *path);
int			ft_chd(t_mini *mini, char *path);
void		chd_str_err(char *path, char *err_str);

// pwd.c
int			ft_pwd(t_mini *mini);

// exit.c
int			ft_exit(t_mini *mini, int tmp_fd);
int			check_numeric(char *str, long long *exit_code);
int			is_longlong(char *str, long long *nbr);
void		exit_str_err(char *path, char *err_str);
int			ft_isspace(char c);
int			is_exit_pipe(t_mini mini);

// env.c
int			ft_env(t_mini *mini, char **args);

// export.c --> to be secured
int			is_bad_assignment(char **args);
int			is_no_equal(char *arg);
char		*dequote(char *str);
int			is_in_twod(char **tab, char *str);
char		*ft_getenv(t_mini *mini, char *varname);
int			ft_export_to_envvars(t_mini *mini, char **args);

// unset.c --> to be secured
int			ft_unset(char **args, t_mini *mini);

/***************temp temp temp *****************/
// void		wait_exitcode(t_mini *mini);

// ft_split.c
char		**ft_split(char const *s, char c);

// temp.c
void		temp_display_tabs(char **token, t_type *type);
// size_t		ft_tabint_len(int *tab);
// size_t		ft_tabtype_len(t_type *tab);

#endif
