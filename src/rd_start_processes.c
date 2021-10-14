/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_start_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:36:19 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/14 10:38:38 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

static bool	init_exec(t_exec *ex)
{
	ft_memset(ex, 0, sizeof(t_exec));
	ex->pipe[READ_END] = -1;
	ex->pipe[WRITE_END] = -1;
	ex->prev_fd = -1;
	ex->p_count = create_processes(ex->proc);
	if (ex->p_count == -1)
		return (false);
	int i = -1;
	int j;
	while (++i < ex->p_count)
	{
		if (!open_infiles(&ex->proc[i]))
			return (false);
		if (!open_outfiles(&ex->proc[i]))
			return (false);
		printf("Last input: `fd = [%d], path = [%s]`, Last output: fd = [%d]\n", ex->proc[i].last_in.fd, ex->proc[i].last_in.file_path, ex->proc[i].last_out);
		printf("CMD ARGS: ");
		j = -1;
		while (ex->proc[i].cmd_argv[++j])
			printf("[%s], ", ex->proc[i].cmd_argv[j]);
	}
	return (true);
}

// static void	reset_exec(t_exec *ex)
// {
// 	ex->pid = 0;
// 	if (ex->curr_envp)
// 		ft_str_array_del(&ex->curr_envp);
// 	close_pipe(ex->pipe);
// 	close(ex->prev_fd);
// 	ex->wstatus = 0;
// }

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

	if (init_exec(&ex))
		return (false);
	return (true);
}
