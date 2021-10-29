/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_ft_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:53:12 by fbarros           #+#    #+#             */
/*   Updated: 2021/10/29 11:53:35 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

bool	ft_env(char **argv)
{
	t_node	*head;

	head = g_mini.env;
	if (argv[1])
		return (err_handler("No such file or directory", 2, false));
	while (head)
	{
		ft_putstr_fd(head->keyword, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(head->content, 1);
		ft_putchar_fd('\n', 1);
		head = head->next;
	}
	return (true);
}

bool	ft_unset(char **argv)
{
	t_node	*param;
	t_node	*tmp;

	param = find_param(argv[1]);
	if (!param)
		return (true);
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
	return (true);
}
