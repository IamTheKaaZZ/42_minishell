/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:12:04 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/30 19:03:17 by bcosters         ###   ########.fr       */
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
//ADD SKIPS TO ESCAPE CHARS {\n \' \" \v \r etc}
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

bool	parse_quotes_spaces(char const **str, size_t *len)
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
		get_next_str_len(str, len, ' ');
	else if (strchr_index(*str, '\"') < strchr_index(*str, '\''))
	{
		start = strchr_index(*str, '\"');
		(*str)++;
		end = strchr_index(*str, '\"');
		*len = end - start;
		dq = 1;
	}
	else if (strchr_index(*str, '\'') < strchr_index(*str, '\"'))
	{
		start = strchr_index(*str, '\'');
		(*str)++;
		end = strchr_index(*str, '\'');
		*len = end - start;
		sq = 1;
	}
	return (true);
}

t_node	*quote_split(const char *str)
{
	t_node	*parsed_list;
	size_t	len;
	char	*token;

	if (!str)
		return (NULL);
	len = 0;
	parsed_list = NULL;
	while (*str)
	{
		if (!parse_quotes_spaces(&str, &len))
		{
			clear_env_list(&parsed_list);
			return (NULL);
		}
		if ((len == 0 && !ft_ischrinset(str, ' ')
				&& !ft_ischrinset(str, '\'') && !ft_ischrinset(str, '\"')))
			len = ft_strlen(str);
		if (!*str)
			break ;
		token = (char *)ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(token, str, len + 1);
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
