/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:12:04 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/30 14:12:57 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

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

	*str += *len;
	*len = 0;
	i = 0;
	while (**str && (**str == c || **str == ' '))
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return (true);
		(*len)++;
		i++;
	}
	if ((*str)[i] == 0 && (c == '\'' || c == '\"'))
		return (err_handler("unclosed quote"));
	return (true);
}

// static bool	find_closing_quote(char const **str, size_t *len, int *dq, int *sq)
// {
// 	if (*dq)
// 	{
// 		if (ft_strchr(*str, '\"') == NULL)
// 			return (err_handler("unclosed quote")); // clear all memory
// 		get_next_str_len(str, len, '\"');
// 		*dq = 0;
// 	}
// 	else if (*sq)
// 	{
// 		if (ft_strchr(*str, '\'') == NULL)
// 			return (err_handler("unclosed quote")); // clear all memory
// 		get_next_str_len(str, len, '\'');
// 		*sq = 0;
// 	}
// 	return (true);
// }

bool	parse_quotes_spaces(char const **str, size_t *len, int *dq, int *sq)
{
	// if (*dq || *sq)
	// {
	// 	if (!find_closing_quote(str, len, dq, sq))
	// 		return (false);
	// }
	(void)sq;
	(void)dq;
	if (ft_strchr(*str, ' ') != NULL
		&& (!ft_strchr(*str, '\'')
			|| ft_strchr(*str, ' ') < ft_strchr(*str, '\''))
		&& (!ft_strchr(*str, '\"')
			|| ft_strchr(*str, ' ') < ft_strchr(*str, '\"')))
		get_next_str_len(str, len, ' ');
	else if (ft_strchr(*str, '\'') != NULL
		&& (!ft_strchr(*str, ' ')
			|| ft_strchr(*str, '\'') < ft_strchr(*str, ' '))
		&& (!ft_strchr(*str, '\"')
			|| ft_strchr(*str, '\'') < ft_strchr(*str, '\"')))
	{
		if (!get_next_str_len(str, len, '\''))
			return (false);
		// *sq = 1;
	}
	else if (ft_strchr(*str, '\"') != NULL
		&& (!ft_strchr(*str, ' ')
			|| ft_strchr(*str, '\"') < ft_strchr(*str, ' '))
		&& (!ft_strchr(*str, '\'')
			|| ft_strchr(*str, '\"') < ft_strchr(*str, '\'')))
	{
		if (!get_next_str_len(str, len, '\"'))
			return (false);
		// *dq = 1;
	}
	else
		get_next_str_len(str, len, ' ');
	return (true);
}

t_node	*quote_split(const char *str)
{
	t_node	*parsed_list;
	size_t	len;
	int		squote;
	int		dquote;
	char	*token;

	if (!str)
		return (NULL);
	len = 0;
	squote = 0;
	dquote = 0;
	parsed_list = NULL;
	while (*str)
	{
		if (!parse_quotes_spaces(&str, &len, &dquote, &squote))
		{
			clear_env_list(&parsed_list);
			return (NULL);
		}
		token = (char *)ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(token, str, len + 1);
		printf("token: %s\n", token);
		if (!parsed_list)
			parsed_list = new_node(token);
		else
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
