/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:14:50 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/07 11:05:51 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

void	ft_echo(t_process proc)
/*	Rought-cut

	expanding variables ??
		var search function
	*/
{
	int		i;
	bool	nl;

	nl = 1;
	i = 1;
	if (proc.cmd_argv[i])
	{
		if (*proc.cmd_argv[i] && !ft_strcmp(proc.cmd_argv[i], "-n"))
		{
			nl = 0;
			i++;
		}
		while (proc.cmd_argv[i])
		{
			if ((nl && i > 1) || (!nl && i > 2)) // terrible
				ft_putchar_fd(' ', 1);
			if (str_contains_chars(proc.cmd_argv[i], "|<>&")) // for now
				return ;
			ft_putstr_fd(proc.cmd_argv[i++], 1);
		}
	}
	if (nl)
		write(1, "\n", 1);
	g_mini.exit_code = 0;
}

void	ft_cd(t_process proc)
/** WAITING FOR ~ TO BE DEALT WITH
 * if starting with '~' look for $HOME
	change $PWD*/
{
	char	err[100];
	char	*path;
	char	**env_var;

	env_var = NULL;
	path = proc.cmd_argv[1];
	if (!path)
		return ;
	ft_bzero(err, 100);
	/*PROTO*/
	if (*path == '~')
	{
		if (chdir(find_param(&g_mini.env, "HOME")->content))
		{
			err_handler("chdir find_param err!!!!!!!!");
			return ;
		}
		path++;
	}
	/*PROTO*/
	if (path && chdir(path) == -1)
	{
		ft_strlcat(err, "cd: ", 5);
		ft_strlcat(err, proc.cmd_argv[1], ft_strlen(proc.cmd_argv[1]));
		err_handler(err);
		return ;
	}
	path = getcwd(NULL, 0);
	env_var = &find_param(&g_mini.env, "PWD")->content;
	if (!path || !env_var)
	{
		ft_strlcat(err, "cd: ", 5);
		ft_strlcat(err, proc.cmd_argv[1], ft_strlen(proc.cmd_argv[1]));
		err_handler(err);
		return ;
	}
	free(*env_var);
	*env_var = path;
	g_mini.exit_code = 0;
}

void	ft_pwd(t_process proc)
/*char *
  getcwd(char *buf, size_t size);
*/
{
	char	*buf;

	buf = NULL;
	if (proc.cmd_argv[1] && !ft_strchr("<>|", *proc.cmd_argv[1])) //<--[!?]
	{
		g_mini.exit_code = 2;
		err_handler("pwd: too many arguments");
	}
	else
	{
		buf = getcwd(NULL, 0);
		if (!buf)
		{
			free(buf);
			g_mini.exit_code = 2;
			err_handler("pwd: Failed to get current working directory.");
		}
		ft_putendl_fd(buf, 1);
		free(buf);
	}
	g_mini.exit_code = 0;
}

void	ft_exit(t_process proc, int i)
{
	g_mini.exit_code = i;
	if (proc.cmd_argv[1])
	{
		if (proc.cmd_argv[2])
		{
			g_mini.exit_code = 2;
			err_handler("exit: too many arguments");
			return ;
		}
		while (proc.cmd_argv[1][++i])
		{
			if (proc.cmd_argv[1][i] == '+')
				continue ;
			if (!ft_isdigit(proc.cmd_argv[1][i]))
			{
				err_handler("exit: numeric argument required");
				g_mini.exit_code = 255;
			}
		}
		if (!g_mini.exit_code)
			g_mini.exit_code = ft_atoi(proc.cmd_argv[1]);
	}
	ft_putstr_fd("exit\n", 1);
	exit(g_mini.exit_code + ft_clear_data());
}
