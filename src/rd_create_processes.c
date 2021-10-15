/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_create_processes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:51:34 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/13 11:09:30 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/**
 * Everything before a '|' or the end of argv is split into a job
 *  =>	Order of execution is important
 *  =>	processes are created (left to right), later executed right to left
 * 	INPUT:
 * 		PRIORITIES:
 * 			1.	Here_doc input (and error checking) (in order if multiple)
 * 			"<< help cat << EOF << lol << l"
 * 				=> all go off in order, only last one counts
 * 			2.	Input files	(and error checking)
 * 			3.	Input from command (and error checking)
 * EXAMPLE: "< logfile cat << EOF < lel"
 * 	-> here_doc until EOF then error on lel because it doesn't exist
 * 	OUTPUT:
 * 		PRIORITIES:
 * 			1. Last redirected output gets the output
 * 			=> echo hello > file1 > file2 > file3 => file3 gets the final output
 * 				=> rest is empty
 * 			=> echo hello > f1 > f2 >> f3 => same but f3 gets appended each time
*/

static void	fill_lists(t_process *proc, char **argv, int *i, int *j)
{
	if (ft_strequal(argv[*i], "|")) //save the last in and out
	{
		proc[*j].cmd_argv = list_to_argv(proc[*j].command);
		clear_env_list(&proc[*j].command);
		proc[*j].last_inf = find_tail(proc[*j].infiles);
		proc[*j].last_outf = find_tail(proc[*j].outfiles);
		(*j)++; //add a hardcap (j > 99 => ERROR too many processes)
	}
	else if (ft_strequal(argv[*i], "<<"))
		add_to_tail(&proc[*j].infiles, new_node("heredoc", argv[++*i]));
	else if (ft_strequal(argv[*i], "<"))
		add_to_tail(&proc[*j].infiles, new_node(NULL, argv[++*i]));
	else if (ft_strequal(argv[*i], ">"))
		add_to_tail(&proc[*j].outfiles, new_node("trunc", argv[++*i]));
	else if (ft_strequal(argv[*i], ">>"))
		add_to_tail(&proc[*j].outfiles, new_node("append", argv[++*i]));
	else
		add_to_tail(&proc[*j].command, new_node(NULL, argv[*i]));
}

static void	fill_input_lists(t_node **here_docs, t_node **files, t_node *temp)
{
	while (temp != NULL)
	{
		if (ft_strequal("heredoc", temp->keyword))
			add_to_tail(here_docs, new_node(temp->keyword, temp->content));
		else
			add_to_tail(files, new_node(temp->keyword, temp->content));
		temp = temp->next;
	}
}

static void	order_by_priority(t_node **infiles)
{
	t_node	*here_docs;
	t_node	*files;
	t_node	*temp;

	here_docs = NULL;
	files = NULL;
	temp = *infiles;
	fill_input_lists(&here_docs, &files, temp);
	clear_env_list(infiles);
	temp = files;
	while (temp != NULL)
	{
		add_to_tail(&here_docs, new_node(temp->keyword, temp->content));
		temp = temp->next;
	}
	clear_env_list(&files);
	*infiles = here_docs;
}

int	create_processes(t_process *proc)
{
	int	i;
	int	j;
	int	proccount;

	i = -1;
	j = 0;
	while (g_mini.argv[++i])
		fill_lists(proc, g_mini.argv, &i, &j);
	proccount = j + 1;
	while (j--)
		order_by_priority(&proc[j].infiles);
	return (proccount);
}
