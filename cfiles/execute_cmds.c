/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:29:35 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/28 13:01:39 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

static int	init_exec(t_exec *ex, char **argv)
{
	int	i;

	ft_memset(ex, 0, sizeof(t_exec));
	ex->pipe[READ_END] = -1;
	ex->pipe[WRITE_END] = -1;
	ex->prev_fd = -1;
	ex->in.fd = -1;
	ex->out.fd = -1;
	i = 0;
	while (*argv)
	{
		if (ft_strequal(argv[i], "|")
			&& ft_strequal(argv[i], "<") && ft_strequal(argv[i], "<<")
			&& ft_strequal(argv[i], ">") && ft_strequal(argv[i], ">>"))
			i++;
		argv++;
	}
	ex->cmds = (t_command *)ft_calloc(i + 1, sizeof(t_command));
	if (!ex->cmds)
		return (err_handler("malloc"));
	return (EXIT_SUCCESS);
}

void	close_pipe(int *pipe)
{
	close(pipe[READ_END]);
	close(pipe[WRITE_END]);
	pipe[READ_END] = -1;
	pipe[WRITE_END] = -1;
}

static void	reset_exec(t_exec *ex)
{
	ex->pid = 0;
	if (ex->curr_envp)
		ft_str_array_del(&ex->curr_envp);
	close_pipe(ex->pipe);
	close(ex->prev_fd);
	ex->wstatus = 0;
	close(ex->in.fd);
	if (ex->in.file_path)
		ft_strdel(&ex->in.file_path);
	close(ex->out.fd);
	if (ex->out.file_path)
		ft_strdel(&ex->out.file_path);
	if (ex->limiter)
		ft_strdel(&ex->limiter);
	while (ex->cmds)
	{
		//free all the commands and their arguments
	}
	ft_bzero(ex->err, 100);
}

/**
 * 	AS IF ARGV = command, flags/arguments, etc, |<>
 * ->	| as argv[0] is a syntax error
 * ->	<< EOF with "<<" as argv[0] still works without command
 * 	BUT: DOESN'T DO ANYTHING -> << EOF >> file creates empty file
 *  	-> STILL OPENS AN INPUTSTREAM BEFORE DOING NOTHING
 * -> "> file": creates an empty file
 * -> "< file": opens and closes the file succesfully (exit_code 0)
 * -> CASE:"wc < file" == "< file wc": redirects input from file to wc
 * -> CASE:"<< EOF wc" == "wc << EOF": Opens inputstream and sends it to wc
 * -> CASE: "cat << EOF" => EXPANDS ALL VARIABLES (ignoring quotes)
 * -> IMPORTANT: Split in jobs => everything before | or end is a job
*/

int	executor(char **argv)
{
	int			i;
	t_exec		ex;

	if (init_exec(&ex, argv))
		return ;
	i = -1;
	while (argv[++i])
	{
		if (ft_strequal(argv[0], "|"))
			return (err_handler(concat_err(ex.err, SYNTAX, "|")));
		if (!syntax_error_check(argv, ex.err, i))
			break ;
		if (ft_strequal(argv[i], "<"))
			if (!open_file_as_input(&ex, argv[++i]))
				break ;
		if (ft_strequal(argv[i], "<<"))
		{
			//open here_doc and save lines temporarily
		}
		if (ft_strequal(argv[i], ">"))
		{
			ex.out.fd = open(argv[++i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (ex.out.fd == -1)
				return (err_handler(argv[i]));
		}
		if (ft_strequal(argv[i], ">>"))
		{
			ex.out.fd = open(argv[++i], O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (ex.out.fd == -1)
				return (err_handler(argv[i]));
		}

		while (argv[i] && !ft_strequal(argv[i], "|")
			&& !ft_strequal(argv[i], "<") && !ft_strequal(argv[i], "<<")
			&& !ft_strequal(argv[i], ">") && !ft_strequal(argv[i], ">>"))
		{
			//collect command and possible flags / arguments
		}
	}
	return (EXIT_SUCCESS);
}
