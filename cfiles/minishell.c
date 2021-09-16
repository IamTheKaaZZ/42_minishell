/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:56:12 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/16 16:59:33 by bcosters         ###   ########.fr       */
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
		printf("\n%hhu\n", g_mini.exit_code);
	}
	if (sig == SIGQUIT)
	{
		write(1, "minishell42: ", 14);
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
		ft_echo(&g_mini);
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
	// else
	// 	ft_path(mini);
}

//OBSOLETE function since getenv("PATH") does the trick

char	**ft_get_path(t_minishell *mini)
{
	t_list	*temp;

	temp = mini->env;
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
*/

void	ft_init(char **argv, char **env)
{
	char	*temp_prompt;

	ft_memset(&g_mini, 0, sizeof(t_minishell));
	temp_prompt = ft_strtrim(argv[0], "./");
	g_mini.prompt = ft_strjoin(temp_prompt, "42: ");
	if (!g_mini.prompt)
		ft_error_exit(&g_mini, "Error creating prompt string");
	ft_strdel(&temp_prompt);
	// mini->input = NULL;
	// mini->argv = NULL;
	g_mini.env = ft_env_list(env, &g_mini);
	if (!g_mini.env)
		ft_error_exit(&g_mini, "Malloc error while creating env list");
	g_mini.path = ft_get_path(&g_mini);
	if (!g_mini.path)
		ft_error_exit(&g_mini, "No PATH variable found");
	if (tcgetattr(STDIN_FILENO, &g_mini.term) != 0)
		ft_error_exit(&g_mini, "Error getting terminal settings");
	g_mini.term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_mini.term) != 0)
		ft_error_exit(&g_mini, "Error setting terminal settings");
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
		exit(ft_clear_data(mini, B));
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
		g_mini.argv = ft_split(g_mini.input, ' ');
		//the escape chars + single/double quotes need to be handled
		functions();
	}
}
