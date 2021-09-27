/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:56:12 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/27 11:35:05 by bcosters         ###   ########.fr       */
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
		//update prompt with cwd
		write(1, g_mini.prompt, ft_strlen(g_mini.prompt));
		rl_redisplay();
	}
	return ;
}

void	functions()
{
	// if (mini->argv[0][0] == '$')
	// 	ft_dollar_sign(mini, 0); // working for argv[1];
	if (!(ft_strncmp(g_mini.input, "echo -n", 7)))
		ft_echon(&g_mini);
	else if (!(ft_strncmp(g_mini.input, "echo", 4)))
		ft_echo();
	// else if (!(ft_strncmp(mini->input, "cd", 2)))
	// 	ft_cd(mini);
	// else if (!(ft_strncmp(mini->input, "pwd", 3)))
	// 	ft_pwd(mini);
	// else if (!(ft_strncmp(mini->input, "export", 6)))
	// 	ft_export(mini);
	/*else if (!(ft_strncmp(mini->input, "unset", 5)))
		ft_unset(mini);*/
	// else if (!(ft_strncmp(mini->input, "env", 3)))
	// 	ft_env(mini);
	// else if (!(ft_strncmp(mini->input, "exit", 4)))
	// 	ft_exit(mini);
	else
		executor(g_mini.argv);
}

//OBSOLETE function since getenv("PATH") does the trick
/*
 * If the path was already set, reset it
*/


char	**ft_get_path(void)
{
	t_list	*temp;

	if (g_mini.path_var)
		ft_str_array_del(&g_mini.path_var);
	temp = g_mini.env;
	while (temp)
	{
		if (!ft_strncmp(temp->keyword, "PATH", 4))
			return (ft_split(temp->content, ':'));
		temp = temp->next;
	}
	return (NULL); // if there is not path then return error
}

// CREATING LIST //

t_list	*ft_env_list(char **env, t_minishell *mini)
{
	int		i;
	t_list	*new;
	t_list	*head;
	t_list	*temp;

	new = NULL;
	head = NULL;
	temp = mini->env;
	i = -1;
	while (env[++i])
	{
		new = ft_lstnew(ft_split(env[i], '='));
		if (!new)
		{
			ft_lstclear(&head, free);
			return (NULL);
		}
		if (!head)
			head = new;
		ft_lstadd_back(&temp, new);
	}
	return (head);
}

/*
*	Initialize the struct
	-> ft_memset => sets all the variables of the struct to 0
	-> Automatically add the missing / to the path variables
*/

void	ft_init(char **argv, char **env)
{
	char	*temp_prompt;

	ft_memset(&g_mini, 0, sizeof(t_minishell));
	temp_prompt = ft_strtrim(argv[0], "./");
	g_mini.prompt = ft_strjoin(temp_prompt, "\033[0;32;1m42\033[0m: ");
	if (!g_mini.prompt)
		ft_error_exit("malloc");
	ft_strdel(&temp_prompt);
	g_mini.env = ft_env_list(env, &g_mini);
	if (!g_mini.env)
		ft_error_exit("malloc");
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
		exit(ft_clear_data());
	if (line != NULL && line[0] != 0)
		add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **env)
{
	ft_init(argv, env);
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
