/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:12:04 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/01 15:04:07 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

/*
 * Handle cases:
	"'$SOMETHING'" => 'expanded'
	'"$SOMETHING"' => "$SOMETHING"
*/

/*
**returns the index to the first occurrence of the character c in the string s*
*/
//ADD SKIPS TO ESCAPE CHARS {\n \' \" \v \r etc} OK
size_t	strchr_index(const char *str, int c)
{
	size_t	i;
	char	*temp;

	temp = (char *)str;
	if (c == 0)
		return (ft_strlen(temp));
	i = 0;
	while (*(temp + i))
	{
		if (*(temp + i + 1) != 0 && *(temp + i) == '\\')
		{
			i += 2;
			continue ;
		}
		if (*(temp + i) == (unsigned char)c)
			return (i);
		i++;
	}
	return (INT_MAX);
}

/*
**	Iteratively finds the next string and corresponding lenght*
**	Every time this gets called.
*/

static bool	get_next_str_len(char const **str, size_t *len, char c)
{
	size_t	i;

	*len = 0;
	i = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return (true);
		(*len)++;
		i++;
	}
	return (true);
}

/**
 * normal split AND double quotes expand vars AND require escaping
 * single quotes: Everything is literal.
*/

bool	parse_quotes_spaces(char const **str, size_t *len, bool *dqu, bool *noq)
{
	size_t			start;
	size_t			end;
	static int		sq;
	static int		dq;

	start = 0;
	*str += *len;
	*len = 0;
	if (dq)
	{
		(*str)++;
		dq = 0;
	}
	if (sq)
	{
		(*str)++;
		sq = 0;
	}
	while (**str && **str == ' ')
		(*str)++;
	if (strchr_index(*str, ' ') < strchr_index(*str, '\"')
		&& strchr_index(*str, ' ') < strchr_index(*str, '\''))
	{
		get_next_str_len(str, len, ' ');
		*noq = true;
	}
	else if (strchr_index(*str, '\"') < strchr_index(*str, '\''))
	{
		start = strchr_index(*str, '\"');
		(*str)++;
		end = strchr_index(*str, '\"');
		if (end == INT_MAX)
			return (err_handler("unclosed double quote"));
		*len = end - start;
		dq = 1;
		*dqu = true;
	}
	else if (strchr_index(*str, '\'') < strchr_index(*str, '\"'))
	{
		start = strchr_index(*str, '\'');
		(*str)++;
		end = strchr_index(*str, '\'');
		if (end == INT_MAX)
			return (err_handler("unclosed single quote"));
		*len = end - start;
		sq = 1;
	}
	return (true);
}



static bool	start_len_expansion(t_expand *exp, char *str)
{
	exp->i = strchr_index(str, '$');
	// Don't expand if not followed by interpretable chars OR when escaped
	if (*(str + exp->i + 1) == 0 || *(str + exp->i + 1) == ' '
		|| *(str + exp->i + 1) == '\\'
		|| (exp->i != 0 && *(str + exp->i - 1) == '\\'))
	{
		// In case of incorrect syntax, skip to the next '$' if there is any
		exp->i = strchr_index(str + exp->i + 1, '$');
	}
	if (!ft_ischrinset(str + exp->i, '$'))
		return (false);
	if (!ft_ischrinset(str + exp->i + 1, ' ')
		&& !ft_ischrinset(str + exp->i + 1, '\\'))
		exp->len = ft_strlen(str + exp->i + 1);
	else
	{
		if (strchr_index(str + exp->i + 1, ' ')
			< strchr_index(str + exp->i + 1, '\\'))
			exp->len = strchr_index(str + exp->i + 1, ' ');
		else
			exp->len = strchr_index(str + exp->i + 1, '\\');
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
 * INTERPRET THE TOKEN when needed
 * -> EXPAND: $... env parameters -> expand them if they exist
 * 		otherwise: delete the entire sequence until the next whitespace
 * -> ESCAPE: '\' when followed by a char (\n, \", \v, etc)
*/

char	*process_token(char const *str, size_t *len, bool dq, bool noq)
{
	char		*tmp;
	t_expand	exp;

	tmp = (char *)ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(tmp, str, len + 1);
	if (!dq && !noq)
		return (tmp);
	ft_bzero(&exp, sizeof(t_expand));
	while (ft_ischrinset(tmp, '$'))
	{
		if (!start_len_expansion(&exp, tmp))
			break ;
		expand_and_join(&exp, &tmp);
	}
	//remove escape '\' in cases: \$ \" '\\'
	exp.i = -1;
	while (tmp[++exp.i])
	{
		if (tmp[exp.i] == '\\')
		{
			if (tmp[exp.i + 1] != 0 && (tmp[exp.i + 1] == '$'
					|| (tmp[exp.i + 1] == '\"') || (tmp[exp.i + 1] == '\\')))
			{
				if (!escape_slashes(&exp, &tmp))
					break ;
			}
			if (!dq && noq && (tmp[exp.i + 1] != 0) || tmp[exp.i + 1] != ' ')
			{
				if (!escape_slashes(&exp, &tmp))
					break ;
			}
		}
	}
}

t_node	*quote_split(const char *str)
{
	t_node	*parsed_list;
	size_t	len;
	char	*token;
	bool	dquote;
	bool	no_quote;

	if (!str)
		return (NULL);
	len = 0;
	parsed_list = NULL;
	dquote = false;
	no_quote = false;
	while (*str)
	{
		if (!parse_quotes_spaces(&str, &len, &dquote, &no_quote))
		{
			clear_env_list(&parsed_list);
			return (NULL);
		}
		if ((len == 0 && !ft_ischrinset(str, ' ')
				&& !ft_ischrinset(str, '\'') && !ft_ischrinset(str, '\"')))
			len = ft_strlen(str);
		if (!*str)
			break ;
		token = process_token(str, &len, &dquote, &no_quote);
		printf("len = %lu ,token: [%s]\n", len, token);
		add_to_tail(&parsed_list, new_node(token));
	}
	return (parsed_list);
}

void	check_for_quotes(void)
{
	bool	singleq;
	bool	doubleq;
	t_node	*parsed_list;

	singleq = false;
	doubleq = false;
	if (ft_ischrinset(g_mini.input, SINGLEQ))
		singleq = true;
	if (ft_ischrinset(g_mini.input, DOUBLEQ))
		doubleq = true;
	if (singleq || doubleq)
	{
		parsed_list = quote_split(g_mini.input);
		if (!parsed_list)
			return ;
	}
	else
	{
		g_mini.argv = ft_split(g_mini.input, ' ');
		if (!g_mini.argv)
			return ;
	}
}
