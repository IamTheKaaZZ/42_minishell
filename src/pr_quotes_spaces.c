/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_quotes_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:32:37 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/08 16:55:20 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/*
**	Iteratively finds the next string and corresponding lenght*
**	Every time this gets called.
*/

static void	get_next_str_len(t_parse *p, char c)
{
	size_t	i;

	*p->len = 0;
	i = 0;
	while (**p->str && **p->str == c)
		(*p->str)++;
	while ((*p->str)[i])
	{
		if ((*p->str)[i] == c)
		{
			p->bools->no_quote = true;
			return ;
		}
		(*p->len)++;
		i++;
	}
	p->bools->no_quote = true;
}

static bool	find_quote_str(t_parse *p, int *sq, int *dq, char quote)
{
	p->start = strchr_index(*(p->str), quote);
	if ((!*dq && p->start > 0) || (!*sq && p->start > 0))
	{
		if (!*dq && !*sq)
			p->bools->no_quote = true;
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
		p->bools->dquote = true;
		*dq = 1;
	}
	else if (quote == '\'')
		*sq = 1;
	return (true);
}

static void	init_parse(t_parse *p, size_t *len, t_prbools *b, const char **str)
{
	p->start = 0;
	p->end = 0;
	p->len = len;
	p->str = str;
	p->bools = b;
	p->bools->space_found = false;
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
	{
		p->bools->space_found = true;
		(*(p->str))++;
	}
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

	init_parse(&p, len, b, str);
	skip_spaces_quotes(&p, &dq, &sq);
	if (char_before_others(*str, ' ', "\"\'"))
		get_next_str_len(&p, ' ');
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
