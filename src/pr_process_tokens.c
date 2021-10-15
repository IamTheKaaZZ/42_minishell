/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_process_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:55:57 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/13 14:45:55 by bcosters         ###   ########.fr       */
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
 * Function to expand ~ to the content of HOME
*/

static char	*expand_tilde(char **token)
{
	char		*temp;

	temp = *token;
	*token = ft_strdup(find_param(&g_mini.env, "HOME")->content);
	if (!*token)
		*token = ft_strdup("");
	ft_strdel(&temp);
	return (*token);
}

/**
 * INTERPRET THE TOKEN when needed
 * -> EXPAND: 1. $... env parameters -> expand them if they exist
 * 			  2. $? -> previous exit code
 * 		otherwise: delete the entire sequence until the next whitespace
 * -> ESCAPE: '\' when followed by a char (\n, \", \v, etc)
*/

char	*process_token(char const *str, size_t *len, t_prbools *b)
{
	char		*token;
	t_expand	exp;

	token = (char *)ft_calloc(*len + 1, sizeof(char));
	ft_strlcpy(token, str, *len + 1);
	if (!b->dquote && !b->no_quote)
		return (token);
	if (ft_strequal(token, "~") && b->no_quote)
		return (expand_tilde(&token));
	ft_bzero(&exp, sizeof(t_expand));
	while (ft_ischrinset(token, '$'))
	{
		if (!start_len_expansion(&exp, token))
			break ;
		expand_and_join(&exp, &token);
	}
	handle_escape_chars(&exp, &token, b);
	b->dquote = false;
	b->no_quote = false;
	return (token);
}
