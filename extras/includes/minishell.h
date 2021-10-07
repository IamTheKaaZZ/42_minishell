/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:52:05 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/07 12:16:08 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft_bonus.h"
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
}				t_minishell;

typedef struct s_file
{
	int			fd;
	char		*file_path;
	struct stat	stats;
}	t_file;

typedef struct s_job
{
	t_node	*head;
	t_file	in[1024];
	t_file	out_fd[1024];
	int		tmp_fd;
	char	*limiter;
	bool	pipe;
}	t_job;

typedef struct s_exec
{
	pid_t		pid;
	char		**curr_envp;
	int			pipe[2];
	int			prev_fd;
	int			wstatus;
	// t_file		in;
	// int			out[1024];
	// t_file		tmp;
	// char		*limiter;
	char		err[100];
	t_job		jobs[100];
}	t_exec;

typedef struct s_expand
{
	size_t	i;
	size_t	len;
	char	*prefix;
	char	*to_expand;
	char	*expanded;
	char	*suffix;
	char	*interpreted;
}	t_expand;

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
char	**list_to_argv(t_node *head);
char	*process_token(char const *str, size_t *len, bool dq, bool noq);
size_t	strchr_index(const char *str, int c);
bool	str_contains_chars(const char *str, char *charset);
bool	char_before_others(const char *str, char c, char *charset);

/**
 * 2.	LIST FUNCTIONS
*/

t_node	*new_env_param(char **param);
t_node	*find_param(t_node **env, char *keyword);
void	remove_param(t_node **env, char	*keyword);
int		count_params(t_node *env);
t_node	*new_node(char *content);
void	add_to_tail(t_node **env, t_node *new);
void	ft_env_list(char **env);
char	**get_current_envp(t_node *head);

/**
 * 3.	BUILTINS
*/

void	ft_echon(t_minishell *mini);
void	ft_echo(void);
void	ft_cd(t_minishell *mini);
void	ft_pwd(t_minishell *mini);
void	ft_export(t_minishell *mini);
void	ft_unset(t_minishell *mini);
void	ft_env(t_minishell *mini);
void	ft_exit(t_minishell *mini);
int		executor(char **argv);
int		open_file_as_input(t_job *j, char *filename, int i);
int		here_doc_as_input(t_job *j);

void	ft_handler(int signal);
char	**ft_get_path(void);
char	*get_full_cmd_path(char *command);

/**
 * 4.	ERROR HANDLING + DATA CLEAN
*/

void	clear_env_list(t_node **env);
int		ft_clear_data(void);
void	ft_error_exit(const char *errmessage);
int		err_handler(const char *errmessage);
bool	syntax_error_check(char **argv, char *err, int i);
bool	unlink_tmp(char *error);

/* DOLLAR */

int		ft_dollar_sign(t_minishell *mini, int i);
#endif