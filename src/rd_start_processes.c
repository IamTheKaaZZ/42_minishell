/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_start_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:36:19 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/13 16:56:33 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

static int	init_exec(t_exec *ex, char **argv)
{
	int	i;

	ft_memset(ex, 0, sizeof(t_exec));
	ex->pipe[READ_END] = -1;
	ex->pipe[WRITE_END] = -1;
	ex->prev_fd = -1;
	//create processes
	return (EXIT_SUCCESS);
}

void	close_pipe(int *pipe)
{
	close(pipe[READ_END]);
	close(pipe[WRITE_END]);
	pipe[READ_END] = -1;
	pipe[WRITE_END] = -1;
}

static void	reset_exec(t_exec *ex)
{
	int	i;

	ex->pid = 0;
	if (ex->curr_envp)
		ft_str_array_del(&ex->curr_envp);
	close_pipe(ex->pipe);
	close(ex->prev_fd);
	ex->wstatus = 0;
	ft_bzero(ex->err, 100);
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


}
