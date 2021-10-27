/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_pipe_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:10:45 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/27 14:51:05 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

void	close_pipe(int *pipe)
{
	close(pipe[READ_END]);
	close(pipe[WRITE_END]);
	pipe[READ_END] = -1;
	pipe[WRITE_END] = -1;
}

bool	open_pipe(int *fd)
{
	if (pipe(fd) < 0)
		return (err_handler("pipe", 1, true));
	return (true);
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
