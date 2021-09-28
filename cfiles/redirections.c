/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:35:51 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/28 13:37:28 by bcosters         ###   ########.fr       */
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
	int			retval;
	char		buffchar;

	retval = read(STDIN_FILENO, &buffchar, 1);
	if (retval == 0) //EOF found
		return (NULL);
	if (retval == -1) // read error
		return ((void *)err_handler("read"));
	while (retval > 0)
	{
		if (ft_ischrinset("\"\\\n", buffchar))
		{

		}
		else
		{
			if (!here_doc)
				here_doc = ft_strjoin_char(NULL, buffchar);
			else
			{
				temp = here_doc;
				here_doc = ft_strjoin_char(temp, buffchar);
				ft_strdel(&temp);
			}
		}
		retval = read(STDIN_FILENO, &buffchar, 1);
	}
}
