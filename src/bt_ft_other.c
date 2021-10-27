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
	g_mini.exit_code = 0;
}

bool	ft_cd(char **argv)
{
	char	err[100];
	char	*path;

	if (!argv[1])
		return (true);
	ft_bzero(err, 100);
	if (chdir(argv[1]) == -1)
	{
		ft_strlcat(err, "cd: ", 5);
		ft_strlcat(err, path, ft_strlen(path) + 5);
		return (err_handler(err, 2, true));
	}
	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_strlcat(err, "cd: ", 5);
		ft_strlcat(err, argv[1], ft_strlen(argv[1]));
		return (err_handler(err, 2, true));
	}
	free(find_param(&g_mini.env, "OLDPWD")->content);
	find_param(&g_mini.env, "OLDPWD")->content = find_param(&g_mini.env, "PWD")->content;
	find_param(&g_mini.env, "PWD")->content = path;
	free(path);
	return (true);
}

void	ft_pwd(char **argv)
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
