/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_input_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:12:04 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/07 14:04:37 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/*
 * Handle cases:
	"'$SOMETHING'" => 'expanded'
	'"$SOMETHING"' => "$SOMETHING"
*/

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

static void	init_parse(t_parse *p, size_t *len, bool *dqu, bool *noq)
{
	p->start = 0;
	p->end = 0;
	p->len = len;
	p->dqu = dqu;
	p->noq = noq;
}

/**
 * normal split AND double quotes expand vars AND require escaping
 * single quotes: Everything is literal.
*/

bool	parse_quotes_spaces(char const **str, size_t *len, bool *dqu, bool *noq)
{
	t_parse		p;
	// size_t			start;
	// size_t			end;
	static int		sq;
	static int		dq;

	init_parse(&p, len, dqu, noq);
	*str += *p->len;
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
	if (char_before_others(*str, ' ', "\"\'"))
	{
		get_next_str_len(str, len, ' ');
		*noq = true;
	}
	else if (char_before_others(*str, '\"', "\'"))
	{
		if (!find_dquote_str(str, &start, &end, len))
			return (false);
		// start = strchr_index(*str, '\"');
		// (*str)++;
		// end = strchr_index(*str, '\"');
		// if (end == INT_MAX)
		// 	return (err_handler("unclosed double quote"));
		// *len = end - start;
		dq = 1;
		*dqu = true;
	}
	else if (char_before_others(*str, '\'', "\""))
	{
		start = strchr_index(*str, '\'');
		(*str)++;
		end = strchr_index(*str, '\'');
		if (end == INT_MAX)
			return (err_handler("unclosed single quote"));
		*len = end - start;
		sq = 1;
	}
	else
	{
		get_next_str_len(str, len, ' ');
		*noq = true;
	}
	return (true);
}

void	split_input(t_node **parsed_list, const char *str,
					bool *dq, bool *noq)
{
	size_t	len;
	char	*token;

	if (!str)
		return ;
	len = 0;
	while (*str)
	{
		if (!parse_quotes_spaces(&str, &len, dq, noq))
		{
			clear_env_list(parsed_list);
			return ;
		}
		if ((len == 0 && !ft_ischrinset(str, ' ')
				&& !ft_ischrinset(str, '\'') && !ft_ischrinset(str, '\"')))
			len = ft_strlen(str);
		if (!*str)
			break ;
		token = process_token(str, &len, *dq, *noq);
		add_to_tail(parsed_list, new_node(token));
	}
}

bool	parse_input_line(void)
{
	t_node	*parsed_list;
	bool	dquote;
	bool	no_quote;
	int		i;
	char	error[100];

	parsed_list = NULL;
	dquote = false;
	no_quote = false;
	split_input(&parsed_list, g_mini.input, &dquote, &no_quote);
	if (!parsed_list)
		return (false);
	g_mini.argv = list_to_argv(parsed_list);
	clear_env_list(&parsed_list);
	if (!g_mini.argv)
		return (false);
	i = -1;
	ft_bzero(error, 100);
	while (g_mini.argv[++i])
		if (!syntax_error_check(g_mini.argv, error, i))
			return (false);
	return (true);
}
