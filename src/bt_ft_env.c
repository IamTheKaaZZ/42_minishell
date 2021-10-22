/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_ft_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:53:12 by fbarros           #+#    #+#             */
/*   Updated: 2021/10/11 13:53:13 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

void	ft_env(t_process *proc)
{
	t_node	*head;

	head = g_mini.env;
	if (proc->command->next)
		err_handler("No such file or directory");
	while (head)
	{
		ft_putstr_fd(head->keyword, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(head->content, 1);
		head = head->next;
	}
	g_mini.exit_code = 0;
}

static void	print_and_free(t_node **line)
{
	ft_putstr("declare -x ");
	ft_putstr((*line)->keyword);
	ft_putstr("=\"");
	ft_putstr((*line)->content);
	ft_putendl("\"");
	free(*line);
	*line = NULL;
}

static void	list_export(t_node *original)
{
	t_node	*listed;
	t_node	*scan;

	while (original)
	{
		add_to_tail(&listed, new_node(original->keyword, original->content));
		original = original->next;
	}
	while (listed->next)
	{
		original = listed;
		scan = original->next;
		while (scan && original)
		{
			if (ft_strcmp(original->keyword, scan->keyword) > 0)
				original = scan;
			scan = scan->next;
		}
		if (original == listed)
			listed = listed->next;
		else
		{
			scan = listed;
			while (scan->next != original && scan->next)
				scan = scan->next;
			scan->next = original->next;
		}
		print_and_free(&original);
	}
	print_and_free(&listed);
}

void	ft_export(t_process *proc)
/*Exporting empty vars*/
{
	char	**split_param;
	t_node	*new;

	if (!proc->command->next)
	{
		list_export(g_mini.env);
		return ;
	}
	/*TMP*/
	if (!ft_strchr(proc->command->next->content, '='))
		return ;
	/*TMP*/
	split_param = ft_split(proc->command->next->content, '=');
	new = new_env_param(split_param);
	if (!new)
	{
		free(split_param[0]);
		free(split_param[1]);
		free(split_param);
		return ;
	}
	add_to_tail(&g_mini.env, new);
	g_mini.exit_code = 0;
}

void	ft_unset(t_process *proc)
{
	t_node	*param;
	t_node	*tmp;

	param = find_param(&g_mini.env, proc->command->next->content);
	if (!param)
		return ;
	tmp = g_mini.env;
	if (tmp != param)
	{
		while (tmp->next != param)
			tmp = tmp->next;
		tmp->next = param->next;
	}
	else
		g_mini.env = g_mini.env->next;
	free(param);
	param = NULL;
	g_mini.exit_code = 0;
}
