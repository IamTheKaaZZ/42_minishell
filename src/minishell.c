/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:56:12 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/13 15:16:20 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

// t_minishell	g_mini;

/*
**	Signal handler
	-> Ctrl-C == SIGINT
	-> Ctrl-\ == SIGQUIT
	-> Ctrl-D == EOF aka close inputstream or shell
*/

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_mini.exit_code = 130;
	}
	if (sig == SIGQUIT)
	{
		//update prompt with cwd ??
		// write(1, g_mini.prompt, ft_strlen(g_mini.prompt));
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	functions(t_process	proc)
/**
 *  Need iterate between args
 * void * preferably kept in struct to save lines and more easibly manageable
 */
{
	if (ft_strequal(proc.command, "echo"))
		ft_echo(proc);
	else if (ft_strequal(proc.command, "env"))
		ft_env(proc);
	else if (ft_strequal(proc.command, "pwd"))
		ft_pwd(proc);
	else if (ft_strequal(proc.command, "cd"))
		ft_cd(proc);
	else if (ft_strequal(proc.command, "exit"))
		ft_exit(proc, -1);
	else if (ft_strequal(proc.command, "unset"))
		ft_unset(proc);
	else if (ft_strequal(proc.command, "export"))
		ft_export(proc);
}

/*
*	Initialize the struct
	-> ft_memset => sets all the variables of the struct to 0
*/

void	ft_init(char **env)
{
	ft_memset(&g_mini, 0, sizeof(t_minishell));
	g_mini.prompt = ft_strdup("minishell\033[0;32;1m42\033[0m: ");
	if (!g_mini.prompt)
		ft_error_exit("malloc");
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
		err_handler("exit");
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
	while (argc)
	{
		g_mini.input = rl_gnl(&g_mini);
		if (!parse_input_line())
			continue ;
		functions();
		// int i = -1;
		// while (g_mini.argv[++i])
		// 	printf("[%s]\n", g_mini.argv[i]);
		ft_str_array_del(&g_mini.argv);
	}
}
