/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_ft_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:14:50 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/29 11:32:14 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

bool	ft_echo(char **argv)
{
	int		i;
	bool	nl;

	nl = 1;
	i = 0;
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
	if (nl)
		write(1, "\n", 1);
	return (true);
}

static void	update_env(char *path)
{
	char	*oldpwd;
	char	*pwd;

	pwd = NULL;
	oldpwd = NULL;
	if (find_param("PWD"))
		pwd = find_param("PWD")->content;
	if (pwd)
	{
		if (find_param("OLDPWD"))
			oldpwd = find_param("OLDPWD")->content;
		if (pwd && oldpwd)
		{
			ft_strdel(&oldpwd);
			find_param("OLDPWD")->content = pwd;
		}
		find_param("PWD")->content = path;
	}
	else
	{
		ft_strdel(&path);
		if (find_param("OLDPWD"))
			ft_bzero(find_param("OLDPWD")->content,
				ft_strlen(find_param("OLDPWD")->content));
	}
}

bool	ft_cd(char **argv)
{
	char	err[100];
	char	*path;

	if (!argv[1])
		path = getenv("HOME");
	else
		path = argv[1];
	ft_bzero(err, 100);
	if (chdir(path) == -1)
	{
		ft_strlcat(err, "cd: ", 5);
		ft_strlcat(err, path, ft_strlen(path) + 5);
		return (err_handler(err, 2, true));
	}
	path = getcwd(NULL, 0);
	if (!path)
		return (err_handler("cd: malloc", 2, true));
	update_env(path);
	return (true);
}

bool	ft_pwd(char **argv)
{
	char	*pwd;

	if (argv[1])
		return (err_handler("pwd: too many arguments", 2, false));
	if (!find_param("PWD"))
		pwd = getcwd(NULL, 0);
	else
		pwd = find_param("PWD")->content;
	ft_putendl_fd(pwd, 1);
	if (!find_param("PWD"))
		ft_strdel(&pwd);
	return (true);
}

bool	ft_exit(char **argv)
{
	int	i;

	i = -1;
	if (argv[1])
	{
		if (argv[2])
			return (err_handler("exit: too many arguments", 2, false));
		while (argv[1][++i])
		{
			if (argv[1][0] == '+' || argv[1][0] == '-')
				continue ;
			if (!ft_isdigit(argv[1][i]))
				err_handler("exit: numeric argument required", 255, false);
		}
		if (g_mini.exit_code != 255)
			g_mini.exit_code = ft_atoi(argv[1]);
	}
	ft_putstr_fd("exit\n", 1);
	exit(ft_clear_data() + g_mini.exit_code);
}
