/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_in_out_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:05:43 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/13 11:12:47 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/**
 * function that handles "< file"
 * -> Checks if the file exists AND if we can read from it
 * -> IF: We can read from it, we open it on fd in
 * -> ELSE: Return an error with the filename
*/

static bool	open_file_as_input(t_file *f, char *filename)
{
	if (stat(filename, &f->stats) != -1
		&& f->stats.st_mode & S_IRUSR)
	{
		f->fd = open(filename, O_RDONLY);
		if (f->fd < 0)
			return (err_handler(filename));
	}
	else
	{
		f->fd = -1;
		return (err_handler(filename));
	}
	f->file_path = filename;
	return (true);
}

/**
 * Open all possible input files but only save the last one in last_in
*/

bool	open_infiles(t_process *proc)
{
	t_node	*temp;
	t_file	tmp;

	temp = proc->infiles;
	tmp.fd = -1;
	while (temp != NULL)
	{
		if (ft_strequal(temp->keyword, "heredoc")
			&& !here_doc_as_input(&tmp, temp->content))
			return (err_handler("here_doc"));
		else if (temp->keyword == NULL
			&& !open_file_as_input(&tmp, temp->content))
			return (false);
		if (temp != proc->last_outf)
		{
			if (temp->keyword != NULL && !unlink_tmp(NULL))
				return (false);
			else if (close(tmp.fd) < 0)
				return (err_handler(temp->content));
		}
		temp = temp->next;
	}
	proc->last_in = tmp;
	clear_env_list(&proc->infiles);
	return (true);
}

/**
 * Open all the possible outfiles but save only the last one as a fd
 * =>	Depending on the keyword open the file with O_TRUNC or O_APPEND
 * =>	IF:	It's not the last one => close the fd
 * =>	ELSE: Save the fd in proc->last_out for later
*/

bool	open_outfiles(t_process *proc)
{
	t_node	*temp;
	int		tmpfd;

	temp = proc->outfiles;
	while (temp != NULL)
	{
		if (ft_strequal(temp->keyword, "trunc"))
			tmpfd = open(temp->content, O_RDWR | O_CREAT | O_TRUNC, 0777);
		else if (ft_strequal(temp->keyword, "append"))
			tmpfd = open(temp->content, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (tmpfd < 0)
			return (err_handler(temp->content));
		if (temp != proc->last_outf)
		{
			if (close(tmpfd) < 0)
				return (err_handler(temp->content));
		}
		temp = temp->next;
	}
	proc->last_out = tmpfd;
	clear_env_list(&proc->outfiles);
	return (true);
}
