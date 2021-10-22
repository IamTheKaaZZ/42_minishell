/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 09:39:25 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/22 15:04:36 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

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
	// if (builtin_or_execve(proc->cmd_argv[0]) == NULL)
	// {
		ex->full_command = get_full_cmd_path(proc->cmd_argv[0]);
		if (ex->full_command)
		{
			if (execve(ex->full_command, proc->cmd_argv, ex->curr_envp) < 0)
				return (err_handler("execve"));
		}
		else
			return (false);
	// }
	// else
	// {
	// 	//call the builtins
	// }
	return (true);
}

void	child_process(t_exec *ex, int i)
{
	if (!open_infiles(&ex->proc[i]))
		exit(g_mini.exit_code);
	if (!open_outfiles(&ex->proc[i]))
		exit(g_mini.exit_code);
	child_redirections(ex, &ex->proc[i], i);
	if (!check_command(ex, &ex->proc[i]))
		exit(g_mini.exit_code);
	exit(EXIT_SUCCESS);
}
