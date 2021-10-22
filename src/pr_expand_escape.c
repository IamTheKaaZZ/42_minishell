/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_expand_escape.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:21:36 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/22 13:22:48 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/**
 * EXPAND THE VARIABLE AND RETURN THE JOINED STRING
 * -> SPLIT: the string into:
 * 			PREFIX:		Anything before the '$'
 * 			TOEXPAND:	The keyword to expand
 * 			SUFFIX:		What is left of the string
 * ->	Delete the starting string
 * -> EXPANDED: Find the parameter by keyword in the env list
 * 			OR: Convert the current exit code to a string
 * -> JOIN: prefix + expanded + suffix => interpreted string
 * ->	Free all extra memory used in the operations
*/

static void	find_expanded(t_expand *exp)
{
	t_node	*param;

	param = find_param(&g_mini.env, exp->to_expand);
	if (ft_strequal(exp->to_expand, "?"))
	{
		printf("exit code to convert: %hu\n", g_mini.exit_code);
		exp->exit_code = ft_itoa((int)g_mini.exit_code);
		printf("Converted string: %s\n", exp->exit_code);
		exp->expanded = exp->exit_code;
	}
	else if (!param)
		exp->expanded = NULL;
	else
		exp->expanded = param->content;
}

void	expand_and_join(t_expand *exp, char **str)
{
	exp->prefix = ft_substr(*str, 0, exp->i);
	exp->to_expand = ft_substr(*str, exp->i + 1, exp->len);
	if (ft_strlen(exp->prefix) + ft_strlen(exp->to_expand) + 1
		== ft_strlen(*str))
		exp->suffix = NULL;
	else
		exp->suffix = ft_substr(*str, exp->i + 1 + exp->len,
				ft_strlen((*str) + exp->i + 1 + exp->len));
	ft_strdel(str);
	find_expanded(exp);
	exp->interpreted = ft_strjoin(exp->prefix, exp->expanded);
	*str = exp->interpreted;
	exp->interpreted = ft_strjoin(*str, exp->suffix);
	ft_strdel(str);
	ft_strdel(&exp->exit_code);
	ft_strdel(&exp->prefix);
	ft_strdel(&exp->to_expand);
	ft_strdel(&exp->suffix);
	*str = exp->interpreted;
}

/**
 * If a character can be escaped => remove the \ from the string
*/

static bool	escape_slashes(t_expand *exp, char **str)
{
	exp->prefix = ft_substr(*str, 0, exp->i);
	exp->suffix = ft_substr(*str, exp->i + 1,
			ft_strlen(*str + exp->i + 1));
	exp->interpreted = ft_strjoin(exp->prefix, exp->suffix);
	ft_strdel(str);
	*str = exp->interpreted;
	ft_strdel(&exp->prefix);
	ft_strdel(&exp->suffix);
	if ((*str)[exp->i] == 0)
		return (false);
	return (true);
}

/**
 * Handle special characters that can be escaped by \
 * CASES: \$ \" '\\' etc...
*/

void	handle_escape_chars(t_expand *exp, char **str, t_prbools *b)
{
	if (ft_strlen(*str) == 1)
		return ;
	exp->i = -1;
	while ((*str)[++exp->i])
	{
		if ((*str)[exp->i] == '\\')
		{
			if ((*str)[exp->i + 1] != 0 && ((*str)[exp->i + 1] == '$'
					|| ((*str)[exp->i + 1] == '\"')
					|| ((*str)[exp->i + 1] == '\\')))
			{
				if (!escape_slashes(exp, str))
					return ;
			}
			if (!b->dquote && b->no_quote
				&& ((*str)[exp->i + 1] != 0 || (*str)[exp->i + 1] != ' '))
			{
				if (!escape_slashes(exp, str))
					return ;
			}
		}
	}
}
