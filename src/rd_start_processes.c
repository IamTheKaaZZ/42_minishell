/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_start_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:36:19 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/14 14:15:49 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

static bool	init_exec(t_exec *ex)
{
	int	i;

	ft_memset(ex, 0, sizeof(t_exec));
	ex->pipe[READ_END] = -1;
	ex->pipe[WRITE_END] = -1;
	ex->prev_fd = -1;
	i = -1;
	while (++i < 100)
	{
		ex->proc[i].last_in.fd = -1;
		ex->proc[i].last_out = -1;
	}
	ex->p_count = create_processes(ex->proc);
	if (ex->p_count == -1)
		return (false);
	int k = -1;
	int j;
	while (++k < ex->p_count)
	{
		if (!open_infiles(&ex->proc[k]))
			return (false);
		if (!open_outfiles(&ex->proc[k]))
			return (false);
		printf("Last input: `fd = [%d], path = [%s]`, Last output: fd = [%d]\n", ex->proc[k].last_in.fd, ex->proc[k].last_in.file_path, ex->proc[k].last_out);
		printf("CMD ARGS: ");
		j = -1;
		while (ex->proc[k].cmd_argv[++j])
			printf("[%s], ", ex->proc[k].cmd_argv[j]);
		printf("\n");
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

	if (!init_exec(&ex))
		return (false);
	return (true);
}
