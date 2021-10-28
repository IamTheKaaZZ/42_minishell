/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_start_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:36:19 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/28 11:04:59 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

static bool	init_exec(t_exec *ex)
{
	int	i;

	ft_memset(ex, 0, sizeof(t_exec));
	ex->pipe[READ_END] = -1;
	ex->pipe[WRITE_END] = -1;
	ex->prev_fd = STDOUT_FILENO;
	i = -1;
	while (++i < 100)
	{
		ex->proc[i].last_in.fd = -1;
		ex->proc[i].last_out = -1;
	}
	ex->p_count = create_processes(ex->proc);
	if (ex->p_count == -1)
		return (false);
	ex->builtin_succes = true;
	unlink(TEMPFILE);
	return (true);
}

static void	reset_exec(t_exec *ex, char **cmdargv)
{
	if (ex->prev_fd != STDOUT_FILENO)
		close(ex->prev_fd);
	ex->prev_fd = ex->pipe[WRITE_END];
	close(ex->pipe[READ_END]);
	if (ft_strequal(cmdargv[0], "exit"))
		ex->builtin_succes = ft_exit(cmdargv);
	else if (ft_strequal(cmdargv[0], "cd"))
		ex->builtin_succes = ft_cd(cmdargv);
	else if (ft_strequal(cmdargv[0], "export"))
		ex->builtin_succes = ft_export(cmdargv);
	else if (ft_strequal(cmdargv[0], "unset"))
		ex->builtin_succes = ft_unset(cmdargv);
	if (cmdargv)
		ft_str_array_del(&cmdargv);
}

static bool	clean_and_wait(t_exec *ex)
{
	close(ex->pipe[WRITE_END]);
	while (wait(&ex->wstatus) > 0)
	{
		if (WEXITSTATUS(ex->wstatus) != EXIT_SUCCESS)
		{
			g_mini.exit_code = WEXITSTATUS(ex->wstatus);
			return (false);
		}
		if (WIFSIGNALED(ex->wstatus))
		{
			if (WTERMSIG(ex->wstatus) == SIGQUIT)
				ft_putendl_fd("\nQuit.", 2);
			else if (WTERMSIG(ex->wstatus) == SIGINT)
				ft_putendl_fd("\nInterrupted.", 2);
			g_mini.exit_code = 128 + WTERMSIG(ex->wstatus);
		}
	}
	if (ex->full_command)
		ft_strdel(&ex->full_command);
	if (!WIFSIGNALED(ex->wstatus) && ex->builtin_succes)
		g_mini.exit_code = 0;
	return (true);
}

// static void	ft_exec(t_process proc)
// {
// 	// ex.pid = fork();
// 	// if (ex.pid == -1)
// 	// 	err_handler
// 	// if (ex.pid == 0)
// 	// {
// 	// 	// child process

// 	// }
// 	// else
// 	// {
// 	// 	// parent process
// 	// }
// 	/**
// 	 * Create child process
// 	 * execve (1st process argument)
// 	 */
// }

bool	start_processes(void)
/**Need further work on "functions", specially exit
 * 
*/
{
	t_exec	ex;
	int		i;

	if (!init_exec(&ex))
		return (false);
	i = ex.p_count;
	while (i--)
	{
		unlink(TEMPFILE);
		ft_strdel(&ex.full_command);
		if (!open_pipe(ex.pipe))
			return (err_handler("pipe", 1, true));
		g_mini.child_dead = false;
		ex.pid = fork();
		if (ex.pid < 0)
			return (err_handler("fork", 1, true));
		if (ex.pid == 0)
			child_process(&ex, i);
		reset_exec(&ex, ex.proc[i].cmd_argv);
	}
	return (clean_and_wait(&ex));
}
