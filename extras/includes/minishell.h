/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:52:05 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/28 10:35:48 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft_bonus.h"
# include "../42_memleak_check/malloc_leak_checker.h"
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/errno.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <string.h>
# include <fcntl.h>

# define SINGLEQ '\''
# define DOUBLEQ '\"'
# define SYNTAX 1
# define UNSPEC 2
# define READ_END 0
# define WRITE_END 1
# define TEMPFILE ".here_doc"

typedef struct s_node
{
	char			*keyword;
	char			*content;
	struct s_node	*next;
}	t_node;

typedef struct s_minishell
{
	char			*input;
	t_node			*env;
	char			**path_var;
	char			**argv;
	struct termios	term;
	char			*prompt;
	char			*cwd;
	unsigned char	exit_code;
	bool			child_dead;
}				t_minishell;

typedef struct s_file
{
	int			fd;
	char		*file_path;
	struct stat	stats;
}	t_file;

typedef struct s_process
{
	t_node	*command;
	t_node	*infiles;
	t_node	*outfiles;
	t_node	*last_inf;
	t_node	*last_outf;
	t_file	last_in;
	int		last_out;
	char	**cmd_argv;
}	t_process;

typedef struct s_exec
{
	pid_t		pid;
	char		**curr_envp;
	char		*full_command;
	int			pipe[2];
	int			prev_fd;
	int			wstatus;
	t_process	proc[100];
	int			p_count;
	bool		builtin_succes;
}	t_exec;

typedef struct s_expand
{
	size_t	i;
	size_t	len;
	char	*exit_code;
	char	*prefix;
	char	*to_expand;
	char	*expanded;
	char	*suffix;
	char	*interpreted;
}	t_expand;

typedef struct s_prbools
{
	bool	sqoute;
	bool	dquote;
	bool	no_quote;
	bool	space_found;
}	t_prbools;

typedef struct s_parse
{
	size_t		start;
	size_t		end;
	size_t		*len;
	const char	**str;
	t_prbools	*bools;
}	t_parse;

typedef struct s_prompt
{
	char	*cwd;
	char	*home;
	char	*path;
	char	*full;
}	t_prompt;

/*
*	GLOBAL VAR
*/

t_minishell	g_mini;

/*
*	FUNCTION PROTOTYPES
*/



/**
 * 1.	PARSING
*/

bool	parse_input_line(void);
bool	parse_quotes_spaces(char const **str, size_t *len, t_prbools *b);
char	**list_to_argv(t_node *head);
char	*process_token(char const *str, size_t *len, t_prbools *b);
void	expand_and_join(t_expand *exp, char **str);
void	handle_escape_chars(t_expand *exp, char **str, t_prbools *b);
size_t	strchr_index(const char *str, int c);
bool	str_contains_chars(const char *str, char *charset);
bool	char_before_others(const char *str, char c, char *charset);
bool	charset_before_other(const char *str, char *charset, char *other);
void	get_next_str_len(t_parse *p, char c);
void	split_redirections(t_parse *p);

/**
 * 2.	LIST FUNCTIONS
*/

t_node	*new_env_param(char **param);
t_node	*find_param(t_node **env, char *keyword);
void	remove_param(t_node **env, char	*keyword);
int		count_params(t_node *env);
t_node	*new_node(char *keyword, char *content);
t_node	*find_tail(t_node *head);
void	add_to_tail(t_node **env, t_node *new);
void	add_new_to_tail(t_node **head, char *keyword, char *content);
void	ft_env_list(char **env);
char	**get_current_envp(void);

/**
 * 3.	BUILTINS
*/

void	functions(char **argv);
bool	ft_echo(char **argv);
bool	ft_cd(char **argv);
bool	ft_pwd(char **argv);
bool	ft_export(char **argv);
bool	ft_unset(char **argv);
bool	ft_env(char **argv);
bool	ft_exit(char **argv);
int		executor(char **argv);

void	ft_handler(int signal);
char	**ft_get_path(void);
char	*get_full_cmd_path(char *command);

/**
 * 4.	PROCESSES
*/

bool	start_processes(void);


int		create_processes(t_process *proc);
bool	here_doc_as_input(t_file *tmp, char *limiter);
bool	open_infiles(t_process *proc);
bool	open_outfiles(t_process *proc);
void	close_pipe(int *pipe);
bool	open_pipe(int *fd);
char	*builtin_or_execve(char *command);
bool	start_processes(void);
void	child_process(t_exec *ex, int i);

/**
 * 5.	ERROR HANDLING + DATA CLEAN
*/

void	clear_list(t_node **head, bool clear);
int		ft_clear_data(void);
void	ft_error_exit(const char *errmessage);
bool	err_handler(const char *errmessage, t_uc e_code, bool print_errno);
bool	syntax_error_check(char **argv, char *err, int i);
bool	check_export_syntax(char *arg);
bool	unlink_tmp(char *error);

/**
 * 6. #RANDOM
*/

void	pretty_prompt(void);
void	intro_message(void);

#endif
