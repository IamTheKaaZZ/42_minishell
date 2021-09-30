/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:29:35 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/30 13:08:04 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

// static int	init_exec(t_exec *ex, char **argv)
// {
// 	int	i;

// 	ft_memset(ex, 0, sizeof(t_exec));
// 	ex->pipe[READ_END] = -1;
// 	ex->pipe[WRITE_END] = -1;
// 	ex->prev_fd = -1;
// 	ft_memset(ex->jobs, 0, 100 * sizeof(t_job));
// 	return (EXIT_SUCCESS);
// }

// void	close_pipe(int *pipe)
// {
// 	close(pipe[READ_END]);
// 	close(pipe[WRITE_END]);
// 	pipe[READ_END] = -1;
// 	pipe[WRITE_END] = -1;
// }

// static void	reset_exec(t_exec *ex)
// {
// 	int	i;

// 	ex->pid = 0;
// 	if (ex->curr_envp)
// 		ft_str_array_del(&ex->curr_envp);
// 	close_pipe(ex->pipe);
// 	close(ex->prev_fd);
// 	ex->wstatus = 0;
// 	ft_bzero(ex->err, 100);
// }

// /**
//  * 	AS IF ARGV = command, flags/arguments, etc, |<>
//  * ->	| as argv[0] is a syntax error
//  * ->	<< EOF with "<<" as argv[0] still works without command
//  * 	BUT: DOESN'T DO ANYTHING -> << EOF >> file creates empty file
//  *  	-> STILL OPENS AN INPUTSTREAM BEFORE DOING NOTHING
//  * -> "> file": creates an empty file
//  * -> "< file": opens and closes the file succesfully (exit_code 0)
//  * -> CASE:"wc < file" == "< file wc": redirects input from file to wc
//  * -> CASE:"<< EOF wc" == "wc << EOF": Opens inputstream and sends it to wc
//  * -> CASE: "cat << EOF" => EXPANDS ALL VARIABLES (ignoring quotes)
//  * -> IMPORTANT: Split in jobs => everything before | or end is a job
// */

// int	create_jobs(t_exec *ex, char **argv)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	j = 0;
// 	if (ft_strequal(argv[0], "|"))
// 		return (err_handler(concat_err(ex->err, SYNTAX, "|")));
// 	while (argv[++i])
// 	{
// 		if (!syntax_error_check(argv, ex->err, i))
// 			return (false);
// 		if (argv[i] != "|")
// 			add_to_tail(&ex->jobs[j].head, new_node(argv));
// 		else
// 			j++;
// 	}
// 	return (true);
// }

// int	executor(char **argv)
// {
// 	int			i;
// 	int			j;
// 	t_exec		ex;

// 	if (init_exec(&ex, argv))
// 		return ;
// 	i = -1;
// 	j = -1;
// 	while (argv[++i])
// 	{
// 		//create as much infiles as < or <<
// 		if (ft_strequal(argv[i], "<"))
// 			if (!open_file_as_input(&ex, argv[++i]))
// 				break ;
// 		if (ft_strequal(argv[i], "<<"))
// 			if (!here_doc_as_input(&ex))
// 				break ;
// 		//create as much outfiles as > or >>
// 		if (ft_strequal(argv[i], ">"))
// 		{
// 			ex.out[++j] = open(argv[++i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 			if (ex.out[j] == -1)
// 				return (err_handler(argv[i]));
// 		}
// 		if (ft_strequal(argv[i], ">>"))
// 		{
// 			ex.out[++j] = open(argv[++i], O_WRONLY | O_CREAT | O_APPEND, 0777);
// 			if (ex.out[j] == -1)
// 				return (err_handler(argv[i]));
// 		}
// 		while (argv[i] && !ft_strequal(argv[i], "|")
// 			&& !ft_strequal(argv[i], "<") && !ft_strequal(argv[i], "<<")
// 			&& !ft_strequal(argv[i], ">") && !ft_strequal(argv[i], ">>"))
// 		{
// 			//collect command and possible flags / arguments
// 		}
// 	}
// 	return (EXIT_SUCCESS);
// }
