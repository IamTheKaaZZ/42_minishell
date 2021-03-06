/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lt_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:01:41 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/29 10:36:13 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/**
 * Modified lst_new for the project
 * -> param = ft_split by '=' on the parameter
 * -> param needs to be free'd either in here or in the fucntion calling this
*/

t_node	*new_env_param(char **param)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->keyword = param[0];
	new->content = param[1];
	new->next = NULL;
	return (new);
}

t_node	*find_tail(t_node *head)
{
	t_node	*temp;

	temp = head;
	while (temp != NULL)
	{
		if (temp->next == NULL)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

/**
 * Modified lst_add_back to fit the project
*/

void	add_to_tail(t_node **env, t_node *new)
{
	if (!*env)
		*env = new;
	else
		find_tail(*env)->next = new;
}

/**
 * Find any param in the env list
*/

t_node	*find_param(char *keyword)
{
	t_node	*temp;

	temp = g_mini.env;
	if (temp != NULL && ft_strequal(temp->keyword, keyword))
		return (temp);
	while (temp != NULL && !ft_strequal(temp->keyword, keyword))
		temp = temp->next;
	if (temp == NULL)
		return (NULL);
	else
		return (temp);
}

/**
 * Count the amount of parameters in the list
*/

int	count_params(t_node *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}
