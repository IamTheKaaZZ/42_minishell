/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:59:50 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/29 13:05:21 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

static char	*get_full_param(t_node *list_item)
{
	char	*prefix;
	char	*full_param;

	prefix = ft_strjoin_char(list_item->keyword, '=');
	full_param = ft_strjoin(prefix, list_item->content);
	ft_strdel(&prefix);
	return (full_param);
}

/**
 * Convert the current env list into an array of strings for execve
*/

char	**get_current_envp(t_node *head)
{
	char	**curr_envp;
	int		n_param;
	int		i;
	t_node	*temp;

	n_param = count_params(g_mini.env) + 1;
	curr_envp = (char **)ft_calloc(n_param, sizeof(char *));
	if (!curr_envp)
		return (NULL);
	i = -1;
	temp = head;
	while (++i < n_param)
	{
		curr_envp[i] = get_full_param(temp);
		if (!curr_envp[i])
			ft_str_array_del(&curr_envp);
		temp = temp->next;
	}
	return (curr_envp);
}

/**
 * Only use the content of the nodes for the pipeline
*/

t_node	*new_node(char *content)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->keyword = NULL;
	new->content = content;
	new->next = NULL;
	return (new);
}