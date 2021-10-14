/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lt_transform_lists.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:01:22 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/14 12:07:24 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

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
 * Only use the content of the nodes for the pipeline and parsing
*/

t_node	*new_node(char *keyword, char *content)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->keyword = keyword;
	new->content = content;
	new->next = NULL;
	return (new);
}

/**
 * Add a new node to the tail of the list
*/

void	add_new_to_tail(t_node **head, char *keyword, char *content)
{
	add_to_tail(head, new_node(keyword, content));
}

/**
 * Convert a linked list with a char *content to an array of strings
 * -> NULL-terminated
*/

char	**list_to_argv(t_node *head)
{
	char	**argv;
	int		n_param;
	int		i;
	t_node	*temp;

	n_param = count_params(head);
	argv = (char **)ft_calloc(n_param + 1, sizeof(char *));
	if (!argv)
		return ((void *)err_handler("malloc"));
	i = -1;
	temp = head;
	while (++i < n_param)
	{
		if (!temp->content)
			break ;
		argv[i] = ft_strdup(temp->content);
		if (!argv[i])
			ft_str_array_del(&argv);
		temp = temp->next;
	}
	return (argv);
}
