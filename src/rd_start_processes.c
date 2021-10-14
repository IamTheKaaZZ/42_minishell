/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_start_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:36:19 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/14 17:46:54 by bcosters         ###   ########.fr       */
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
	//DEBUG
	// int k = -1;
	// int j;
	// while (++k < ex->p_count)
	// {
	// 	if (!open_infiles(&ex->proc[k]))
	// 		return (false);
	// 	if (!open_outfiles(&ex->proc[k]))
	// 		return (false);
	// 	printf("Last input: `fd = [%d], path = [%s]`, Last output: fd = [%d]\n", ex->proc[k].last_in.fd, ex->proc[k].last_in.file_path, ex->proc[k].last_out);
	// 	printf("CMD ARGS: ");
	// 	j = -1;
	// 	while (ex->proc[k].cmd_argv[++j])
	// 		printf("[%s], ", ex->proc[k].cmd_argv[j]);
	// 	printf("\n");
	// }
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

bool	start_processes(void)
{
	t_exec	ex;
	int		i;

	if (!init_exec(&ex))
		return (false);
	i = ex.p_count;
	while (i--)
	{
		if (!open_infiles(&ex.proc[i]))
			return (false);
		if (!open_outfiles(&ex.proc[i]))
			return (false);
		if (!open_pipe(ex.pipe))
			return (err_handler("pipe"));
		ex.pid = fork();
		if (ex.pid < 0)
			return (err_handler("fork"));
		if (ex.pid == 0) //CHILD
		{
			if (ex.proc[i].last_out > 0)
			{
				dup2(ex.proc[i].last_out, STDOUT_FILENO);
				close(ex.proc[i].last_out);
			}
			else
				dup2(ex.prev_fd, STDOUT_FILENO);
			if (ex.proc[i].last_in.fd > 0)
			{
				dup2(ex.proc[i].last_in.fd, STDIN_FILENO);
				close(ex.proc[i].last_in.fd);
			}
			else
				dup2(ex.pipe[READ_END], STDIN_FILENO);
			close_pipe(ex.pipe);
			//check if it's a builtin
			ex.curr_envp = get_current_envp();
			if (execve(get_full_cmd_path(ex.proc[i].cmd_argv[0]), ex.proc[i].cmd_argv, ex.curr_envp) < 0)
				return (err_handler("execve"));
		} //PARENT
		reset_exec(&ex);
	}
	close_pipe(ex.pipe);
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
