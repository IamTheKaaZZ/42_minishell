/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:52:05 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/28 11:28:34 by bcosters         ###   ########.fr       */
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

typedef struct s_env
{
	char			*keyword;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	char			*input;
	t_env			*env;
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

typedef struct s_command
{
	char	*name;
	char	*full_path;
	char	**args;
}	t_command;

typedef struct s_exec
{
	pid_t		pid;
	char		**curr_envp;
	int			pipe[2];
	int			prev_fd;
	int			wstatus;
	t_file		in;
	t_file		out;
	char		*limiter;
	t_command	*cmds;
	char		err[100];
}	t_exec;

/*
*	GLOBAL VAR
*/

t_minishell	g_mini;

/*
*	FUNCTION PROTOTYPES
*/

void	ft_echo(void);
void	ft_cd(void);
void	ft_env(void);
void	ft_pwd(void);


int		executor(char **argv);

void	ft_handler(int signal);
t_env	*new_env_param(char **param);
t_env	*find_param(t_env **env, char *keyword);
void	remove_param(t_env **env, char	*keyword);
int		count_params(t_env *env);
void	add_to_tail(t_env **env, t_env *new);
void	ft_env_list(char **env);
char	**get_current_envp(t_env *head);
char	**ft_get_path(void);
char	*get_full_cmd_path(char *command);
void	check_for_quotes(void);

/* ERROS AND CLEAN */

void	clear_env_list(t_env **env);
int		ft_clear_data(void);
void	ft_error_exit(const char *errmessage);
int		err_handler(const char *errmessage);
bool	syntax_error_check(char **argv, char *err, int i);

/* DOLLAR */

int		ft_dollar_sign(t_minishell *mini, int i);
#endif
