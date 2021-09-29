/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_file_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:50:54 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/29 12:56:24 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

/**
 * function that handles "< file"
 * -> Checks if the file exists AND if we can read from it
 * -> IF: We can read from it, we open it on fd in
 * -> ELSE: Return an error with the filename
*/

int	open_file_as_input(t_job *j, char *filename, int i)
{
	if (stat(filename, &j->in[i].stats) != -1
		&& j->in[i].stats.st_mode & S_IRUSR)
	{
		j->in[i].fd = open(filename, O_RDONLY);
		if (j->in[i].fd == -1)
			return (err_handler(filename));
	}
	else
		return (err_handler(filename));
	return (true);
}

static bool	retval_or_limiter(t_job *j, char **line, int retval)
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
	if (ft_strequal(line, j->limiter))
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

static bool	write_to_tmp(t_job *j, char **line)
{
	int	i;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\\' && (*line)[i + 1] == '\\')
			i++;
		if (write(j->tmp_fd, &(*line)[i], 1) < 0)
		{
			ft_strdel(line);
			return (unlink_tmp("write"));
		}
	}
	if (write(j->tmp_fd, "\n", 1) < 0)
	{
		ft_strdel(line);
		return (unlink_tmp("write"));
	}
	return (true);
}

int	here_doc_as_input(t_job *j)
{
	char		*line;
	int			retval;

	line = NULL;
	j->tmp_fd = open(TEMPFILE, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (j->tmp_fd == -1)
		return (EXIT_FAILURE);
	retval = get_next_line(STDIN_FILENO, &line);
	if (retval_or_limiter(j, &line, retval))
		return (unlink_tmp(NULL));
	while (retval > 0)
	{
		if (!write_to_tmp(j, &line))
			return (EXIT_FAILURE);
		ft_strdel(&line);
		retval = get_next_line(STDIN_FILENO, &line);
		if (retval_or_limiter(j, &line, retval))
			return (EXIT_SUCCESS);
		else
		{
			ft_strdel(&line);
			return (unlink_tmp(NULL));
		}
	}
	return (EXIT_SUCCESS);
}
