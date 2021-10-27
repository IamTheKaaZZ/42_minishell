/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_ft_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:57:18 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/27 15:10:03 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

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

static void	compare_ascii(t_node **original, t_node **listed)
{
	t_node	*scan;

	*original = *listed;
	scan = (*original)->next;
	while (scan && *original)
	{
		if (ft_strcmp((*original)->keyword, scan->keyword) > 0)
			(*original) = scan;
		scan = scan->next;
	}
	if ((*original) == (*listed))
		(*listed) = (*listed)->next;
	else
	{
		scan = *listed;
		while (scan->next != *original && scan->next)
			scan = scan->next;
		scan->next = (*original)->next;
	}
	print_and_free(original);
}

static bool	list_export(t_node *original)
{
	t_node	*listed;

	listed = NULL;
	while (original)
	{
		add_to_tail(&listed, new_node(original->keyword, original->content));
		original = original->next;
	}
	while (listed->next)
	{
		compare_ascii(&original, &listed);
	}
	print_and_free(&listed);
	return (true);
}

static bool	add_to_env(t_node **new, char ***split_param)
{
	*new = new_env_param(*split_param);
	if (!*new)
	{
		ft_str_array_del(split_param);
		err_handler("malloc", 2, true);
		return (false);
	}
	add_to_tail(&g_mini.env, *new);
	ft_str_array_del(split_param);
	return (true);
}

bool	ft_export(char **argv)
{
	char	**split_param;
	t_node	*new;
	int		i;

	if (argv[1] == NULL)
		return (list_export(g_mini.env));
	new = NULL;
	i = 0;
	while (argv[++i])
	{
		if (!check_export_syntax(argv[i]))
			return ;
		split_param = ft_split(argv[i], '=');
		if (!split_param)
			return ;
		else if (find_param(&g_mini.env, split_param[0]))
		{
			new = find_param(&g_mini.env, split_param[0]);
			free(new->content);
			new->content = ft_strdup(ft_strchr(argv[i], '=') + 1);
		}
		else
			if (!add_to_env(&new, &split_param))
				return ;
	}
}
