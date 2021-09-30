/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:56:12 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/29 15:31:56 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

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

void	functions(void)
/*  */
{
	// if (!ft_strncmp(g_mini.input ,"echo", 4))
	if (ft_strequal(*g_mini.argv, "echo"))
		ft_echo();
	// else if (!ft_strncmp(g_mini.input, "env", 3))
	if (ft_strequal(*g_mini.argv, "env"))
		ft_env();
	// else if (!ft_strncmp(g_mini.input, "pwd", 3))
	if (ft_strequal(*g_mini.argv, "pwd"))
		ft_pwd();
	// else if (!ft_strncmp(g_mini.input, "cd", 2))
	if (ft_strequal(*g_mini.argv, "cd"))
		ft_cd();
	else
		executor(g_mini.argv);
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
	if (!line) // EOF
		exit(ft_clear_data());
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
		check_for_quotes();
		functions();
		ft_str_array_del(&g_mini.argv);
	}
}
