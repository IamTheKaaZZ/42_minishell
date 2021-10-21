/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_start_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:36:19 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/21 09:40:30 by bcosters         ###   ########.fr       */
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

static void	clean_and_wait(t_exec *ex)
{
	close(ex->pipe[WRITE_END]);
	while (wait(&ex->wstatus) > 0)
	{
		if (WIFEXITED(ex->wstatus) != true)
		{
			if (WEXITSTATUS(ex->wstatus) != EXIT_SUCCESS)
				err_handler("wait");
		}
	}
	ft_str_array_del(&ex->curr_envp);
	ft_strdel(&ex->full_command);
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
			if (!child_process(&ex, i))
				return (false);
		} //PARENT
		reset_exec(&ex);
	}
	clean_and_wait(&ex);
	return (true);
}
