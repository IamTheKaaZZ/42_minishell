/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_ft_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:57:18 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/27 14:07:22 by bcosters         ###   ########.fr       */
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

static void	list_export(t_node *original)
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
}

static bool	check_syntax(char *arg)
{
	static char	suffix[100] = "': not a valid identifier";
	char		error[300];
	size_t		eq_index;

	ft_bzero(error, 300);
	ft_strlcpy(error, "`", 2);
	if (str_contains_chars(arg, " "))
	{
		eq_index = strchr_index(arg, '=');
		if (char_before_others(arg, ' ', "="))
		{
			ft_strlcat(error, arg + eq_index, 300);
			ft_strlcat(error, suffix, 300);
			printf("error = %s\n", error);
		}
		else if (eq_index + 1 == ' ')
		{
			arg += eq_index + 1;
			while (*arg && ft_isspace(*arg))
				arg++;
			ft_strlcat(error, arg, 300);
			ft_strlcat(error, suffix, 300);
			printf("error = %s\n", error);
		}
		return (err_handler(error));
	}
	return (true);
}

void	ft_export(char **argv)
{
	char	**split_param;
	t_node	*new;

	if (!check_syntax(argv[1]))
	{
		g_mini.exit_code = 2;
		return ;
	}
	split_param = ft_split(argv[1], '=');
	if (!split_param)
		list_export(g_mini.env);
	else if (find_param(&g_mini.env, split_param[0]))
	{
		new = find_param(&g_mini.env, split_param[0]);
		free(new->content);
		new->content = ft_strdup(ft_strchr(argv[1], '=') + 1);
	}
	else
	{
		new = new_env_param(split_param);
		if (!new)
		{
			ft_str_array_del(&split_param);
			err_handler("malloc");
			g_mini.exit_code = 2;
			return ;
		}
		add_to_tail(&g_mini.env, new);
	}
	g_mini.exit_code = 0;
}
