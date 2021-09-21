/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:52:05 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/21 15:06:32 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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

typedef struct s_minishell
{
	char			*input;
	t_list			*env;
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
	t_command	*cmds;
}	t_exec;

/*
*	GLOBAL VAR
*/

t_minishell	g_mini;

/*
*	FUNCTION PROTOTYPES
*/

void	ft_echon(t_minishell *mini);
void	ft_echo(void);
void	ft_cd(t_minishell *mini);
void	ft_pwd(t_minishell *mini);
void	ft_export(t_minishell *mini);
void	ft_unset(t_minishell *mini);
void	ft_env(t_minishell *mini);
void	ft_exit(t_minishell *mini);
void	ft_interpret_input(void);

void	ft_handler(int signal);
char	**get_current_envp(t_list *head);
char	**ft_get_path(void);
char	*get_full_cmd_path(char *command);

/* ERROS AND CLEAN */

int		ft_clear_data(void);
void	ft_clean_input_argv(void);
void	ft_error_exit(const char *errmessage);
int		ft_error_handler(const char *errmessage);

/* DOLLAR */

int		ft_dollar_sign(t_minishell *mini, int i);
#endif
