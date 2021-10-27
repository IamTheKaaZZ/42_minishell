/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_ft_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:14:50 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/27 14:46:13 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

void	ft_echo(char **argv)
/*	Rought-cut

	expanding variables ??
		var search function
	*/
{
	int		i;
	bool	nl;
	// t_node	*tmp;

	nl = 1;
	i = 0;
	// tmp = argv[1];
	if (argv[1])
	{
		if (!ft_strcmp(argv[1], "-n"))
		{
			nl = 0;
			i++;
		}
		while (argv[++i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1])
				ft_putchar_fd(' ', 1);
		}
	}

	// if (g_mini.argv[i]) // if followup  to command
	// {
	// 	if (*g_mini.argv[i] && !ft_strcmp(g_mini.argv[i], "-n")) // if -n flag
	// 	{
	// 		nl = 0;
	// 		i++;
	// 	}
	// 	while (proc.cmd_argv[i])
	// 	{
	// 		if ((nl && i > 1) || (!nl && i > 2)) // terrible
	// 			ft_putchar_fd(' ', 1);
	// 		if (str_contains_chars(proc.cmd_argv[i], "|<>&")) // for now
	// 			return ;
	// 		ft_putstr_fd(proc.cmd_argv[i++], 1);
	// 	}
	// }
	
	if (nl)
		write(1, "\n", 1);
	g_mini.exit_code = 0;
}



void	ft_cd(char **argv)
/** WAITING FOR ~ TO BE DEALT WITH
 * if starting with '~' look for $HOME
	change $PWD*/
{
	char	err[100];
	char	*path;
	char	**env_var;

	env_var = NULL;
	path = argv[1];
	if (!path)
		return ;
	ft_bzero(err, 100);
	if (path && chdir(path) == -1)
	{
		ft_strlcat(err, "cd: ", 5);
		ft_strlcat(err, argv[1], ft_strlen(argv[1]));
		err_handler(err, 2, true);
		return ;
	}
	path = getcwd(NULL, 0);
	env_var = &find_param(&g_mini.env, "PWD")->content;
	if (!path || !env_var)
	{
		ft_strlcat(err, "cd: ", 5);
		ft_strlcat(err, argv[1], ft_strlen(argv[1]));
		err_handler(err, 2, true);
		return ;
	}
	free(find_param(&g_mini.env, "PWD")->content);
	find_param(&g_mini.env, "PWD")->content = path;
	g_mini.exit_code = 0;
}

void	ft_pwd(char **argv)
/*char *
  getcwd(char *buf, size_t size);
*/
{
	char	*buf;

	buf = NULL;
	if (argv[1])
	{
		err_handler("pwd: too many arguments", 2, false);
		return ;
	}
	ft_putendl_fd(find_param(&g_mini.env, "PWD")->content, 1);
	free(buf);
	g_mini.exit_code = 0;
}

void	ft_exit(char **argv, int i)
{
	if (argv[1])
	{
		if (argv[2])
		{
			err_handler("exit: too many arguments", 2, false);
			return ;
		}
		while (argv[1][++i])
		{
			if (argv[1][i] == '+')
				continue ;
			if (!ft_isdigit(argv[1][i]))
				err_handler("exit: numeric argument required", 255, false);
		}
		if (!g_mini.exit_code)
			g_mini.exit_code = ft_atoi(argv[1]);
	}
	ft_putstr_fd("exit\n", 1);
	exit(g_mini.exit_code + ft_clear_data());
}
