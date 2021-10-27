/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_ft_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:53:12 by fbarros           #+#    #+#             */
/*   Updated: 2021/10/27 12:58:10 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

void	ft_env(char **argv)
{
	t_node	*head;

	head = g_mini.env;
	if (argv[1])
		err_handler("No such file or directory");
	while (head)
	{
		ft_putstr_fd(head->keyword, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(head->content, 1);
		ft_putchar_fd('\n', 1);
		head = head->next;
	}
	g_mini.exit_code = 0;
}

void	ft_unset(char **argv)
{
	t_node	*param;
	t_node	*tmp;

	param = find_param(&g_mini.env, argv[1]);
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
