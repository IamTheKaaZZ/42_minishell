/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_quotes_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:32:37 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/08 11:04:59 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/*
**	Iteratively finds the next string and corresponding lenght*
**	Every time this gets called.
*/

static void	get_next_str_len(const char **str, size_t *len, char c, bool *noq)
{
	size_t	i;

	*len = 0;
	i = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return ;
		(*len)++;
		i++;
	}
	*noq = true;
}

static bool	find_quote_str(t_parse *p, int *sq, int *dq, char quote)
{
	p->start = strchr_index(*(p->str), quote);
	if ((!*dq && p->start > 0) || (!*sq && p->start > 0))
	{
		*p->len = p->start;
		return (true);
	}
	(*(p->str))++;
	p->end = strchr_index(*(p->str), quote);
	if (p->end == INT_MAX && quote == '\"')
		return (err_handler("unclosed double quote"));
	if (p->end == INT_MAX && quote == '\'')
		return (err_handler("unclosed single quote"));
	*p->len = p->end - p->start;
	if (quote == '\"')
	{
		*p->dqu = true;
		*dq = 1;
	}
	else if (quote == '\'')
		*sq = 1;
	return (true);
}

static void	init_parse(t_parse *p, size_t *len, bool *dqu, const char **str)
{
	static int	space_found;

	p->start = 0;
	p->end = 0;
	p->len = len;
	p->dqu = dqu;
	p->space_found = &space_found;
	p->str = str;
	*p->str += *p->len;
	*p->len = 0;
}

static void	skip_spaces_quotes(t_parse *p, int *dq, int *sq)
{
	if (*dq)
	{
		(*(p->str))++;
		*dq = 0;
	}
	if (*sq)
	{
		(*(p->str))++;
		*sq = 0;
	}
	while (**(p->str) && **(p->str) == ' ')
		(*(p->str))++;
}

/**
 * normal split AND double quotes expand vars AND require escaping
 * single quotes: Everything is literal.
*/

bool	parse_quotes_spaces(char const **str, size_t *len, t_prbools *b)
{
	t_parse		p;
	static int	sq;
	static int	dq;

	init_parse(&p, len, &b->dquote, str);
	skip_spaces_quotes(&p, &dq, &sq);
	if (char_before_others(*str, ' ', "\"\'"))
		get_next_str_len(p.str, p.len, ' ', &b->no_quote);
	else if (char_before_others(*str, '\"', "\'"))
	{
		if (!find_quote_str(&p, &sq, &dq, '\"'))
			return (false);
	}
	else if (char_before_others(*str, '\'', "\""))
	{
		if (!find_quote_str(&p, &sq, &dq, '\''))
			return (false);
	}
	return (true);
}
