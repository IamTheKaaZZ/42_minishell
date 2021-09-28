/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:35:51 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/28 17:09:01 by bcosters         ###   ########.fr       */
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

int	here_doc_as_input(t_exec *ex)
{
	static char	*here_doc;
	char		*temp;
	char		*line;
	int			retval;
	int			i;

	line = NULL;
	retval = get_next_line(STDIN_FILENO, &line);
	if (retval == 0)
		return (here_doc);
	if (retval == -1)
		return ((void *)err_handler("get next line"));
	if (ft_strequal(line, ex->limiter))
	{
		ft_strdel(&line);
		return (here_doc);
	}
	while (retval > 0)
	{
		i = -1;
		while (line[++i])
		{
			if (line[i] == '\\' && line[i + 1] == '\\')
				i++;
			temp = here_doc;
			here_doc = ft_strjoin_char(temp, line[i]);
			ft_strdel(&temp);
		}
		temp = here_doc;
		here_doc = ft_strjoin_char(temp, '\n');
		ft_strdel(&temp);
		retval = get_next_line(STDIN_FILENO, &line);
		if (retval == 0)
			return (here_doc);
		if (retval == -1)
			return ((void *)err_handler("get next line"));
		if (ft_strequal(line, ex->limiter))
		{
			ft_strdel(&line);
			return (here_doc);
		}
	}
}
