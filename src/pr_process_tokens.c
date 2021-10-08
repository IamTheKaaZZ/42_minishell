/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_process_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:55:57 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/08 12:14:50 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/**
 * Find the starting index and length of the env variable to be expanded
 * ->	Don't expand if not followed by interpretable chars OR when escaped
 * ->	In case of incorrect syntax, skip to the next '$' if there is any
*/

static bool	start_len_expansion(t_expand *exp, char *str)
{
	exp->i = strchr_index(str, '$');
	if (*(str + exp->i + 1) == 0 || *(str + exp->i + 1) == ' '
		|| *(str + exp->i + 1) == '\\'
		|| (exp->i != 0 && *(str + exp->i - 1) == '\\'))
		exp->i = strchr_index(str + exp->i + 1, '$');
	if (exp->i == INT_MAX || !ft_ischrinset(str + exp->i, '$'))
		return (false);
	if (!str_contains_chars(str + exp->i, " \\\'\"$"))
		exp->len = ft_strlen(str + exp->i + 1);
	else
	{
		if (char_before_others(str + exp->i + 1, ' ', "\\\'\"$"))
			exp->len = strchr_index(str + exp->i + 1, ' ');
		else if (char_before_others(str + exp->i + 1, '\\', "\'\"$"))
			exp->len = strchr_index(str + exp->i + 1, '\\');
		else if (char_before_others(str + exp->i + 1, '\'', "\"$"))
			exp->len = strchr_index(str + exp->i + 1, '\'');
		else if (char_before_others(str + exp->i + 1, '\"', "$"))
			exp->len = strchr_index(str + exp->i + 1, '\"');
		else
			exp->len = strchr_index(str + exp->i + 1, '$');
	}
	return (true);
}

/**
 * EXPAND THE VARIABLE AND RETURN THE JOINED STRING
 * -> SPLIT: the string into:
 * 			PREFIX:		Anything before the '$'
 * 			TOEXPAND:	The keyword to expand
 * 			SUFFIX:		What is left of the string
 * ->	Delete the starting string
 * -> EXPANDED: Find the parameter by keyword in the env list
 * -> JOIN: prefix + expanded + suffix => interpreted string
 * ->	Free all extra memory used in the operations
*/

static void	expand_and_join(t_expand *exp, char **str)
{
	t_node	*param;

	exp->prefix = ft_substr(*str, 0, exp->i);
	exp->to_expand = ft_substr(*str, exp->i + 1, exp->len);
	if (ft_strlen(exp->prefix) + ft_strlen(exp->to_expand) + 1
		== ft_strlen(*str))
		exp->suffix = NULL;
	else
		exp->suffix = ft_substr(*str, exp->i + 1 + exp->len,
				ft_strlen((*str) + exp->i + 1 + exp->len));
	ft_strdel(str);
	param = find_param(&g_mini.env, exp->to_expand);
	if (!param)
		exp->expanded = NULL;
	else
		exp->expanded = param->content;
	exp->interpreted = ft_strjoin(exp->prefix, exp->expanded);
	*str = exp->interpreted;
	exp->interpreted = ft_strjoin(*str, exp->suffix);
	ft_strdel(str);
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

static void	handle_escape_chars(t_expand *exp, char **str, t_prbools *b)
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

/**
 * INTERPRET THE TOKEN when needed
 * -> EXPAND: $... env parameters -> expand them if they exist
 * 		otherwise: delete the entire sequence until the next whitespace
 * -> ESCAPE: '\' when followed by a char (\n, \", \v, etc)
*/

char	*process_token(char const *str, size_t *len, t_prbools *b)
{
	char		*tmp;
	t_expand	exp;

	tmp = (char *)ft_calloc(*len + 1, sizeof(char));
	ft_strlcpy(tmp, str, *len + 1);
	if (!b->dquote && !b->no_quote)
		return (tmp);
	ft_bzero(&exp, sizeof(t_expand));
	while (ft_ischrinset(tmp, '$'))
	{
		if (!start_len_expansion(&exp, tmp))
			break ;
		expand_and_join(&exp, &tmp);
	}
	handle_escape_chars(&exp, &tmp, b);
	b->dquote = false;
	b->no_quote = false;
	return (tmp);
}
