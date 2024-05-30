/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:56:00 by caguillo          #+#    #+#             */
/*   Updated: 2024/05/31 00:25:48 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2
# define ERR_RHD "minishell: warning: here-document end-of-file expected\n"
# define ERR_STX "minishell: syntax error\n"
# define ERR_SQX "minishell: syntax error (squote opened)\n"
# define ERR_DQX "minishell: syntax error (dquote opened)\n"
# define ERR_HDX "minishell: syntax error near unexpected token `"
# define ERR_GNL "minishell: gnl: Can't read input\n"
# define ERR_MAL "minishell: malloc failed\n"
# define ERR_NHD "minishell: maximum here-document count exceeded\n"
# define ERR_AMB "minishell: *: ambiguous redirect\n"
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
# define EXIT_OPT 125
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
	ARG,
	EMPTY
}			t_type;

typedef struct s_mini
{
	char	*fprompt;
	char	**token;
	t_type	*type;
	int		type_len;
	int		stx_err_idx;
	char	**cmd_arg;
	char	**paths;
	char	**envvars;
	int		fd_in;
	int		fd_out;
	int		fd[2];
	int		prev_fd0;
	int		is_pipe;
	pid_t	last_pid;
	int		status;
	int		is_last_pid;
	int		exitcode;
	int		lastcode;
	int		is_heredoc;
	int		hd_pos;
	int		hd_idx;
	char	*lim;
	int		hd_fd;
	char	**hd_name;
}			t_mini;

typedef struct s_trash
{
	char	*formats;
	char	**splitted;
	int		i;
}			t_trash;

// main.c
void		mini_shell(t_mini *mini);
int			read_prompt(t_mini *mini);
void		read_prompt_next(t_mini *mini);
void		quit(t_mini *mini, char *prompt, int k);
// wait.c
void		wait_exitcode(t_mini *mini);
// main_init_utils.c
void		main_init_utils(int *pexit, int *gvar, int argc, char **argv);
void		close_and_save_fd(t_mini *mini);
// check_quote.c
int			check_quotes(char *str);
int			check_quotes_output(int s_open, int d_open);
void		check_quoted_type(t_type *type, char **token);
char		*remove_quote(char *str);
// check_quote2.c
int			inside_quotes(char const *str, int i);
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
// split_fprompt_utils.c
char		**free_splits(char **split, int i, int j);
// syntax_checker.c
int			check_syntax(t_mini *mini);
int			check_pipe(t_mini *mini);
int			check_type_sequence(t_mini *mini);
// heredoc_setting.c
void		open_heredoc(t_mini *mini, int nbr_hd);
void		fill_heredoc(t_mini *mini, int fd);
// heredoc_name.c
char		**create_hd_name(t_mini *mini);
char		*heredoc_name(void);
// heredoc_to_exec.c
int			nbr_heredoc(t_mini mini);
void		get_heredoc(t_mini *mini, int start);
int			get_heredoc_idx(t_mini *mini, int hd_pos);
void		unlink_free_hdname(t_mini *mini);
int			check_heredoc(t_mini *mini);
// files.c
int			is_infile(t_mini *mini, int start);
void		open_infile(t_mini *mini, char *infile);
int			is_outfile(t_mini *mini, int start);
void		check_files(t_mini *mini, int start);
// files_utils.c
int			is_ambigous(char *str);
void		free_ambigous(t_mini *mini, char *str);
// to_exec.c
int			nbr_block(t_mini mini);
void		blocks_to_exec(t_mini *mini, char **envp, int nbr_block);
// to_exec_child.c
void		child(t_mini *mini, char **envp, int start);
void		close_prev_pipe(t_mini mini);
// exec.c
int			check_slash(char *str);
void		exec_arg(t_mini mini, char **envp, int start);
void		exec_cmd(t_mini mini, char **envp);
void		exec_abs(t_mini mini, char **envp);
void		is_a_directory(t_mini *mini, char *is_cmd_or_dir);
// type.c
t_type		*create_type(t_mini *mini);
t_type		get_type(char **token, int i);
t_type		get_type2(char **token, int i);
void		check_type(t_mini *mini);
void		check_type_block(t_mini *mini, int start);
// type_utils.c
int			get_cmd_idx(t_mini mini, int start);
int			ft_tabstr_len(char **tab);
// path.c
void		get_paths(t_mini *mini, char **envp);
void		slash_paths(t_mini *mini);
int			check_in_str(char *s1, char *s2);
char		*check_path(char **paths, char **cmd);
// buitins.c
int			is_builtin(t_mini mini, int start);
void		builtin(t_mini *mini, int start);
int			builtin_infile(t_mini *mini, int i);
int			builtin_outfile(t_mini *mini, int i);
// buitins_utils.c
int			builtin_files(t_mini *mini, int start);
// buitins_utils2.c
void		create_cmd_arg(t_mini *mini, int start);
int			len_cmd_arg(t_mini mini, int start);
// free_close_exit.c
void		close_exit(t_mini mini, int k);
void		perror_close_exit(char *err, t_mini *mini, int k);
void		perror_open_free(t_mini *mini, char *filename);
void		free_close_exit(t_mini *mini, int exit_code, int is_paths);
void		putstr_error(char *cmd0, char *err_str);
// free_close_exit2.c
void		perr_cl_ex_save(char *err, t_mini *mini, int k, int save_fd);
// signal.c
void		manage_signal(void);
void		handle_sigint(int signal);
void		handle_sigint_in_child(int signal);
void		handle_sigquit_in_child(int sign);
void		handle_sigint_in_hd(int signal);
// dollar.c
void		check_dollar(t_mini *mini);
// dollar_utils.c
int			idx_dollar(char *str, int start);
int			end_dollar(char *str, int start);
int			is_loop(char *varname, char *varvalue);
char		*get_before(char *tok, int start);
char		*get_after(char *tok, int start);
// envvars_manager.c
char		*add_envvars(t_mini *mini, char *str);
char		*envvars_unquoter(char *str);
char		**rm_from_tokens(char **tokens, int i);
void		envvars_manager(char **tokens, t_mini *mini);
// envvars_utils.c
char		*add_to_formats(char *formats, char f);
char		*count_formats(char *str, char *formats);
// envvars_utils2.c
char		*find_next_element(char *str, t_trash *trash, t_mini *mini);
// ft_getenv.c
char		*ft_getenv(t_mini *mini, char *varname);

//--------------------- BUILTINS ------------------------------------//
// chd.c
int			checkfor_dir(char *path);
int			ft_chd(t_mini *mini);
void		chd_str_err(char *path, char *err_str);
// echo.c
int			ft_echo(char **args);
// env.c
int			ft_env(t_mini *mini, char **args);
void		update_env(t_mini *mini);
// exit.c
int			ft_exit(t_mini *mini, int tmp_fd);
int			check_numeric(char *str, long long *exit_code);
int			is_longlong(char *str, long long *nbr);
int			is_longlong_plus(char *str, long long *nbr, int i);
int			is_longlong_minus(char *str, long long *nbr, int i);
// exit_utils.c
void		exit_str_err(char *path, char *err_str);
int			ft_isspace(char c);
int			is_in_pipe(t_mini mini);
int			is_space_inside(char *str);
// export.c
char		**append(char **tab, char *str);
void		replace(char **tab, char *str);
void		sort_exp(char **env);
void		export_void(char **env);
int			ft_export_to_envvars(t_mini *mini, char **args);
// export_utils.c
int			is_in_twod(char **tab, char *str);
int			is_as_child(t_mini mini);
// export_utils2.c
int			is_valid(char *str);
int			is_equal(char *arg);
void		exp_str_err(char *arg, char *err_str);
int			is_valid_start(char *str);
int			is_valid_name(char *str);
// pwd.c
int			ft_pwd(void);
char		*get_pwd(void);
void		update_pwd(t_mini *mini, char *varequal, char *pwd);
// unset.c
int			ft_unset(char **args, t_mini *mini);

// /***************temp temp temp *****************/
// // void		wait_exitcode(t_mini *mini);

// // ft_split.c
// char		**ft_split(char const *s, char c);

// // temp.c
// void		temp_display_tabs(char **token, t_type *type);
// // size_t		ft_tabint_len(int *tab);
// // size_t		ft_tabtype_len(t_type *tab);

// tokenizer(t_mini *mini);
// tokenizer
// int			blocks_counter(char *fprompt);
// char		**token_init(char **token, char *fprompt);
// int			is_sep(char c);
// int			is_in_quotes(char *prompt, int i);
// void

#endif
