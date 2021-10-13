/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_file_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:50:54 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/13 09:48:15 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/**
 * function that handles "< file"
 * -> Checks if the file exists AND if we can read from it
 * -> IF: We can read from it, we open it on fd in
 * -> ELSE: Return an error with the filename
*/

int	open_file_as_input(t_process *j, char *filename)
{
	if (stat(filename, &j->last_in.stats) != -1
		&& j->last_in.stats.st_mode & S_IRUSR)
	{
		j->last_in.fd = open(filename, O_RDONLY);
		if (j->last_in.fd == -1)
			return (err_handler(filename));
	}
	else
		return (err_handler(filename));
	return (true);
}

static bool	retval_or_limiter(char *limiter, char **line, int retval)
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
	if (ft_strequal(*line, limiter))
	{
		ft_strdel(line);
		return (true);
	}
	return (true);
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

static bool	write_to_tmp(int tmp_fd, char **line)
{
	int	i;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\\' && (*line)[i + 1] == '\\')
			i++;
		if (write(tmp_fd, &(*line)[i], 1) < 0)
		{
			ft_strdel(line);
			return (unlink_tmp("write"));
		}
	}
	if (write(tmp_fd, "\n", 1) < 0)
	{
		ft_strdel(line);
		return (unlink_tmp("write"));
	}
	return (true);
}

int	here_doc_as_input(int tmp_fd, char *limiter)
{
	char		*line;
	int			retval;

	line = NULL;
	tmp_fd = open(TEMPFILE, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (tmp_fd == -1)
		return (EXIT_FAILURE);
	retval = get_next_line(STDIN_FILENO, &line);
	if (retval_or_limiter(limiter, &line, retval))
		return (unlink_tmp(NULL));
	while (retval > 0)
	{
		if (!write_to_tmp(tmp_fd, &line))
			return (EXIT_FAILURE);
		ft_strdel(&line);
		retval = get_next_line(STDIN_FILENO, &line);
		if (retval_or_limiter(limiter, &line, retval))
			return (EXIT_SUCCESS);
		else
		{
			ft_strdel(&line);
			return (unlink_tmp(NULL));
		}
	}
	return (EXIT_SUCCESS);
}
