/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_in_out_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:05:43 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/26 15:44:44 by bcosters         ###   ########.fr       */
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
			return (err_handler(filename, 1));
	}
	else
	{
		f->fd = -1;
		return (err_handler(filename, 1));
	}
	f->file_path = filename;
	return (true);
}

static bool	close_or_delete(t_node *temp, t_node *last, t_file *t, t_file *f)
{
	if (ft_strequal(temp->content, last->content))
	{
		close(t->fd);
		*f = *t;
		return (true);
	}
	if (temp->keyword != NULL)
	{
		if (!unlink_tmp(NULL))
			return (false);
	}
	else if (close(t->fd) < 0)
		return (err_handler(temp->content, 1));
	return (true);
}

/**
 * Open all possible input files but only save the last one in last_in
 * =>	here documents have the keyword "heredoc"
 * =>	normal input files have NULL as keyword
 * 		=>	check for errors for both
 * =>	If it's not the last one:
 * 		=>	delete the temp file if it's a heredoc
 * 		=>	close the fd is it's a normal file
 * =>	If it's the last one => save it in last_in
 * =>	Clear the list after use
*/

bool	open_infiles(t_process *proc)
{
	t_node	*temp;
	t_file	tmp;
	t_file	final;

	temp = proc->infiles;
	tmp.fd = -1;
	final.file_path = NULL;
	while (temp != NULL)
	{
		if (ft_strequal(temp->keyword, "heredoc"))
		{
			if (!here_doc_as_input(&tmp, temp->content))
				return (err_handler("here_doc", 1));
		}
		else if (!open_file_as_input(&tmp, temp->content))
			return (false);
		if (!close_or_delete(temp, proc->last_inf, &tmp, &final))
			return (false);
		temp = temp->next;
	}
	if (final.file_path != NULL)
		open_file_as_input(&proc->last_in, final.file_path);
	clear_list(&proc->infiles, false);
	return (true);
}

/**
 * Open all the possible outfiles but save only the last one as a fd
 * =>	Depending on the keyword open the file with O_TRUNC or O_APPEND
 * =>	IF:	It's not the last one => close the fd
 * =>	ELSE: Save the fd in proc->last_out for later
 * =>	Clear the list after use
*/

bool	open_outfiles(t_process *proc)
{
	t_node	*temp;
	int		tmpfd;

	temp = proc->outfiles;
	tmpfd = -1;
	while (temp != NULL)
	{
		if (ft_strequal(temp->keyword, "trunc"))
			tmpfd = open(temp->content, O_RDWR | O_CREAT | O_TRUNC, 0777);
		else if (ft_strequal(temp->keyword, "append"))
			tmpfd = open(temp->content, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (tmpfd < 0)
			return (err_handler(temp->content, 1));
		if (temp != proc->last_outf)
		{
			if (close(tmpfd) < 0)
				return (err_handler(temp->content, 1));
		}
		temp = temp->next;
	}
	proc->last_out = tmpfd;
	clear_list(&proc->outfiles, false);
	return (true);
}
