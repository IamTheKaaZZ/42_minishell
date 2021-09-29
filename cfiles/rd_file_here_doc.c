/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_file_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:50:54 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/29 11:57:57 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

/**
 * function that handles "< file"
 * -> Checks if the file exists AND if we can read from it
 * -> IF: We can read from it, we open it on fd in
 * -> ELSE: Return an error with the filename
*/

int	open_file_as_input(t_exec *ex, char *filename)
{
	if (stat(filename, &ex->in.stats) != -1
		&& ex->in.stats.st_mode & S_IRUSR)
	{
		ex->in.fd = open(filename, O_RDONLY);
		if (ex->in.fd == -1)
			return (err_handler(filename));
	}
	else
		return (err_handler(filename));
	return (true);
}

static bool	retval_or_limiter(t_exec *ex, char **line, int retval)
{
	if (retval == 0)
	{
		ft_strdel(line);
		return (true);
	}
	if (retval == -1)
	{
		ft_strdel(line);
		return (err_handler("get next line"));
	}
	if (ft_strequal(line, ex->limiter))
	{
		ft_strdel(line);
		return (true);
	}
}

bool	unlink_tmp(char *error)
{
	if (unlink(TEMPFILE) < 0)
		return (err_handler("unlink"));
	else if (error != NULL)
		return (err_handler(error));
	else
		return (true);
}

static bool	write_to_tmp(t_exec *ex, char **line)
{
	int	i;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\\' && (*line)[i + 1] == '\\')
			i++;
		if (write(ex->tmp.fd, &(*line)[i], 1) < 0)
		{
			ft_strdel(line);
			return (unlink_tmp("write"));
		}
	}
	if (write(ex->tmp.fd, "\n", 1) < 0)
	{
		ft_strdel(line);
		return (unlink_tmp("write"));
	}
	return (true);
}

int	here_doc_as_input(t_exec *ex)
{
	char		*line;
	int			retval;

	line = NULL;
	ex->tmp.fd = open(TEMPFILE, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (ex->tmp.fd == -1)
		return (EXIT_FAILURE);
	retval = get_next_line(STDIN_FILENO, &line);
	if (retval_or_limiter(ex, &line, retval))
		return (unlink_tmp(NULL));
	while (retval > 0)
	{
		if (!write_to_tmp(ex, &line))
			return (EXIT_FAILURE);
		ft_strdel(&line);
		retval = get_next_line(STDIN_FILENO, &line);
		if (retval_or_limiter(ex, &line, retval))
			return (EXIT_SUCCESS);
		else
		{
			ft_strdel(&line);
			return (unlink_tmp(NULL));
		}
	}
	return (EXIT_SUCCESS);
}
