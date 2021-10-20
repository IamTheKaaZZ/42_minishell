/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_start_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:36:19 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/20 17:09:17 by bcosters         ###   ########.fr       */
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
	unlink(TEMPFILE);
	return (true);
}

static void	reset_exec(t_exec *ex)
{
	if (ex->prev_fd != STDOUT_FILENO)
		close(ex->prev_fd);
	ex->prev_fd = ex->pipe[WRITE_END];
	close(ex->pipe[READ_END]);
}

/**
 * Function that checks if the command is a builtin or not
 * RETURNS:
 * 		=>	Name of builtin if matched
 * 		=>	NULL if not matched
*/

char	*builtin_or_execve(char *command)
{
	static char	builtins[7][7] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	int			i;

	i = -1;
	while (++i < 7)
	{
		if (ft_strequal(command, builtins[i]))
			return (builtins[i]);
	}
	return (NULL);
}

static void	child_redirections(t_exec *ex, t_process *proc, int i)
{
	if (proc->last_out > 0)
	{
		dup2(proc->last_out, STDOUT_FILENO);
		close(proc->last_out);
	}
	else if (ex->prev_fd != STDOUT_FILENO)
	{
		dup2(ex->prev_fd, STDOUT_FILENO);
		close(ex->prev_fd);
	}
	if (proc->last_in.fd > 0)
	{
		dup2(proc->last_in.fd, STDIN_FILENO);
		close(proc->last_in.fd);
	}
	else if (i != 0)
	{
		dup2(ex->pipe[READ_END], STDIN_FILENO);
	}
	close_pipe(ex->pipe);
}

static bool	check_command(t_exec *ex, t_process *proc)
{
	ex->curr_envp = get_current_envp();
	if (builtin_or_execve(proc->cmd_argv[0]) == NULL)
	{
		ex->full_command = get_full_cmd_path(proc->cmd_argv[0]);
		if (ex->full_command)
		{
			if (execve(ex->full_command, proc->cmd_argv, ex->curr_envp) < 0)
				return (err_handler("execve"));
		}
	}
	else
	{
		//call the builtins
	}
	return (true);
}

bool	start_processes(void)
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
			return (err_handler("pipe"));
		ex.pid = fork();
		if (ex.pid < 0)
			return (err_handler("fork"));
		if (ex.pid == 0) //CHILD
		{
			if (!open_infiles(&ex.proc[i]))
				return (false);
			if (!open_outfiles(&ex.proc[i]))
				return (false);
			child_redirections(&ex, &ex.proc[i], i);
			if (!check_command(&ex, &ex.proc[i]))
				return (false);
		} //PARENT
		reset_exec(&ex);
	}
	close(ex.pipe[WRITE_END]);
	while (wait(&ex.wstatus) > 0)
	{
		if (WIFEXITED(ex.wstatus) != true)
		{
			if (WEXITSTATUS(ex.wstatus) != EXIT_SUCCESS)
				err_handler("wait");
		}
	}
	return (true);
}
