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

void	ft_echo(t_process *proc)
/*	Rought-cut

	expanding variables ??
		var search function
	*/
{
	int		i;
	bool	nl;
	t_node	*tmp;

	nl = 1;
	i = 1;
	tmp = proc->command->next;
	if (tmp)
	{
		if (!ft_strcmp(tmp->content, "-n"))
		{
			nl = 0;
			tmp = tmp->next;
		}
		while (tmp)
		{
			ft_putstr_fd(tmp->content, 1);
			if (tmp->next)
				ft_putchar_fd(' ', 1);
			tmp = tmp->next;
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

void	ft_cd(t_process *proc)
/** WAITING FOR ~ TO BE DEALT WITH
 * if starting with '~' look for $HOME
	change $PWD*/
{
	char	err[100];
	char	*path;
	char	**env_var;

	env_var = NULL;
	path = proc->command->next->content;
	if (!path)
		return ;
	ft_bzero(err, 100);
	if (path && chdir(path) == -1)
	{
		ft_strlcat(err, "cd: ", 5);
		ft_strlcat(err, proc->cmd_argv[1], ft_strlen(proc->cmd_argv[1]));
		err_handler(err);
		return ;
	}
	path = getcwd(NULL, 0);
	env_var = &find_param(&g_mini.env, "PWD")->content;
	if (!path || !env_var) // ...
	{
		ft_strlcat(err, "cd: ", 5);
		ft_strlcat(err, proc->cmd_argv[1], ft_strlen(proc->cmd_argv[1]));
		err_handler(err);
		return ;
	}
	free(*env_var);
	*env_var = path;
	g_mini.exit_code = 0; // ...
}

void	ft_pwd(t_process *proc)
/*char *
  getcwd(char *buf, size_t size);
*/
{
	char	*buf;

	buf = NULL;
	if (proc->command->next)
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

void	ft_exit(t_process *proc, int i)
{
	g_mini.exit_code = i;
	if (proc->command->next)
	{
		if (proc->command->next->next)
		{
			g_mini.exit_code = 2;
			err_handler("exit: too many arguments");
			return ;
		}
		while (proc->command->next->content[++i])
		{
			if (proc->command->next->content[i] == '+')
				continue ;
			if (!ft_isdigit(proc->command->next->content[i]))
			{
				err_handler("exit: numeric argument required");
				g_mini.exit_code = 255;
			}
		}
		if (!g_mini.exit_code)
			g_mini.exit_code = ft_atoi(proc->command->next->content);
	}
	ft_putstr_fd("exit\n", 1);
	exit(g_mini.exit_code + ft_clear_data());
}
