/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_start_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:36:19 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/13 14:23:43 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

static int	init_exec(t_exec *ex, char **argv)
{
	// int	i;
	(void)argv;

	ft_memset(ex, 0, sizeof(t_exec));
	ex->pipe[READ_END] = -1;
	ex->pipe[WRITE_END] = -1;
	ex->prev_fd = -1;
	create_processes(ex->proc);
	return (EXIT_SUCCESS);
}

void	close_pipe(int *pipe)
{
	close(pipe[READ_END]);
	close(pipe[WRITE_END]);
	pipe[READ_END] = -1;
	pipe[WRITE_END] = -1;
}

// static void	reset_exec(t_exec *ex)
// {
// 	// int	i;

// 	ex->pid = 0;
// 	if (ex->curr_envp)
// 		ft_str_array_del(&ex->curr_envp);
// 	close_pipe(ex->pipe);
// 	close(ex->prev_fd);
// 	ex->wstatus = 0;
// 	ft_bzero(ex->err, 100);
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
			return (builtins[i]); // ??
	}
	return (NULL);
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

	i = -1;
	init_exec(&ex, g_mini.argv);
	// while (++i < ex.p_count)
	// {
		// error state and return value ??
		if (builtin_or_execve(ex.proc->command->content))
			functions(&ex.proc[0]);
		else
			ft_exec(ex.proc[i]);
	// 		break ;
	// }
	return(1);
}
