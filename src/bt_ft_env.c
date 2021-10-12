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

void	ft_env(void)
/* t_node functions (-> env_list.c):
	
	t_node *
-	new_env_param(char **param)

	static t_node *
-	find_tail(t_node *head)

	void
-	add_to_tail(t_node **env, t_node *new)

	t_node *
-	find_param(t_node **env, char *keyword)

	int
-	count_params(t_node *env)
*/
{
	t_node	*head;

	head = g_mini.env;
	while (head)
	{
		ft_putstr_fd(head->keyword, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(head->content, 1);
		head = head->next;
	}
}

void	ft_export(void)
/**
 * Where are we keeping "not exported env vars"?
*/
{
	char	**split_param;
	t_node	*new;

	if (!g_mini.argv[1])
		return ;
	/*TMP*/
	if (!ft_strchr(g_mini.argv[1], '='))
		return ;
	/*TMP*/
	split_param = ft_split(g_mini.argv[1], '=');
	new = new_env_param(split_param);
	if (!new)
	{
		free(split_param[0]);
		free(split_param[1]);
		free(split_param);
		return ;
	}
	add_to_tail(&g_mini.env, new);
}

void	ft_unset(void)
{
	t_node	*param;
	t_node	*tmp;

	param = find_param(&g_mini.env, g_mini.argv[1]);
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
}
