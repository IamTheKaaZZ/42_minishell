/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:07:41 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/21 11:14:59 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

static char	*get_full_param(t_list *list_item)
{
	char	*prefix;
	char	*full_param;

	prefix = ft_strjoin_char(list_item->keyword, '=');
	full_param = ft_strjoin(prefix, list_item->content);
	ft_strdel(&prefix);
	return (full_param);
}

char	**get_current_envp(t_list *head)
{
	char	**curr_envp;
	int		n_param;
	int		i;
	t_list	*temp;

	n_param = ft_lstsize(g_mini.env) + 1;
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

char	*get_full_cmd_path(char *command)
{
	t_file	cmd;
	int		i;

	i = -1;
	while (g_mini.path[++i])
	{
		cmd.file_path = ft_strjoin(g_mini.path[i], command);
		if (stat(cmd.file_path, &cmd.file_stat) != -1)
		{
			
		}
	}
}