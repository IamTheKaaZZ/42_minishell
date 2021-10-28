/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:56:12 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/28 12:48:48 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/*
**	Signal handler
	-> Ctrl-C == SIGINT
	-> Ctrl-\ == SIGQUIT
	-> Ctrl-D == EOF aka close inputstream or shell
*/

void	ft_handler(int sig)
{
	if (sig == SIGCHLD)
		g_mini.child_dead = true;
	if (sig == SIGINT)
	{
		g_mini.exit_code = 130;
		if (g_mini.child_dead)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	if (sig == SIGQUIT)
	{
		if (g_mini.child_dead)
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
	return ;
}

void	functions(char **argv)
{
	if (ft_strequal(argv[0], "echo"))
		ft_echo(argv);
	else if (ft_strequal(argv[0], "env"))
		ft_env(argv);
	else if (ft_strequal(argv[0], "pwd"))
		ft_pwd(argv);
}

/*
*	Initialize the struct
	-> ft_memset => sets all the variables of the struct to 0
*/

void	ft_init(char **env)
{
	ft_memset(&g_mini, 0, sizeof(t_minishell));
	g_mini.child_dead = true;
	ft_env_list(env);
	if (!g_mini.env)
		ft_error_exit("env list creation");
	if (tcgetattr(STDIN_FILENO, &g_mini.term) != 0)
		ft_error_exit("tcgetattr");
	g_mini.term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_mini.term) != 0)
		ft_error_exit("tcsetattr");
}

/*
**	Memory leak protected version of gnl with readline
	-> Clears previously allocated memory for 'line' before reading again
	-> Reads from user with the given prompt
	-> IF it's a valid line
		-> Add it to the line history (ignoring empty lines)
	-> RETURN the read line;
*/

char	*rl_gnl(t_minishell *mini)
{
	static char	*line;

	if (line)
		ft_strdel(&line);
	line = readline(mini->prompt);
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		exit(ft_clear_data());
	}
	if (line != NULL && line[0] != 0)
		add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	ft_init(env);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	signal(SIGCHLD, ft_handler);
	intro_message();
	while (argc)
	{
		pretty_prompt();
		g_mini.input = rl_gnl(&g_mini);
		if (!parse_input_line())
			continue ;
		start_processes();
		ft_str_array_del(&g_mini.argv);
		unlink(TEMPFILE);
	}
}
