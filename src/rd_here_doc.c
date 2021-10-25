/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:04:58 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/20 15:39:12 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/**
 * Function to check the return value and the line given by GNL
 * RETVAL:
 * 			== 0 	-> EOF found, delete the line, exit
 * 			== -1	-> GNL error, delete the line, exit
 * LINE:	== limiter => delete the line, exit
*/

static bool	retval_or_limiter(char *limiter, char **line, int retval)
{
	if (retval == 0)
	{
		ft_strdel(line);
		return (false);
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

/**
 * Function to delete the temp file on error OR when no longer needed
*/

bool	unlink_tmp(char *error)
{
	if (unlink(TEMPFILE) < 0)
		return (err_handler("unlink"));
	else if (error != NULL)
		return (err_handler(error));
	else
		return (true);
}

/**
 * Function to write the line to the temp file
 * =>	write the line to the file char by char (escaping slashes)
 * =>	write a newline instead of a null-term into the file
 * =>	check for write errors
*/

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
	ft_strdel(line);
	return (true);
}

/**
 * Init function
 * =>	init line as NULL
 * =>	open the tempfile and check for errors
 * =>	set file_path to .heredoc
*/

static bool	init_here_doc(t_file *tmp, char **line)
{
	*line = NULL;
	tmp->fd = open(TEMPFILE, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (tmp->fd == -1)
		return (err_handler("creation of temporary file"));
	tmp->file_path = TEMPFILE;
	return (true);
}

/**
 * Open a here document as input: Take input from STDIN until limiter is found
 * 1.	INIT:	init line, open temporary file, set file_path to .here_doc
 * 2.	DOWHILE: (retval > 0)
 * 			=>	print heredoc prompt
 * 			=>	get a line from stdin
 * 			=>	check the retval for errors or EOF and line for the limiter
 * 				=>	On error: delete the temp file and the line
 * 				=>	line gets deleted when the limiter has been found
 * 			=>	if a line is found => write it to tmp && delete it
*/

bool	here_doc_as_input(t_file *tmp, char *limiter)
{
	char		*line;
	int			retval;

	if (!init_here_doc(tmp, &line))
		return (false);
	write(STDOUT_FILENO, "> ", 2);
	retval = get_next_line(STDIN_FILENO, &line);
	if (!retval_or_limiter(limiter, &line, retval))
		return (unlink_tmp(NULL));
	if (!line)
		return (true);
	while (retval > 0)
	{
		if (!write_to_tmp(tmp->fd, &line))
			return (false);
		write(STDOUT_FILENO, "> ", 2);
		retval = get_next_line(STDIN_FILENO, &line);
		if (!retval_or_limiter(limiter, &line, retval))
			return (unlink_tmp(NULL));
		if (!line)
			return (true);
	}
	return (true);
}
