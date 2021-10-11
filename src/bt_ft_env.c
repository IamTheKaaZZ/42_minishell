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
	while (head->next)
	{
		ft_putstr_fd(head->keyword, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(head->content, 1);
		head = head->next;
	}
}

// void	ft_export(void)
// {

// }

// void	ft_unset(void)
// {

// }