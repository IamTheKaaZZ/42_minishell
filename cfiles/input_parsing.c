/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:12:04 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/29 18:09:15 by bcosters         ###   ########.fr       */
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

static void	get_next_str_len(char const **str, size_t *len, char c)
{
	size_t	i;

	*str += *len;
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
}

t_node	*quote_split(const char *str, bool sq, bool dq)
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
	while (*str)
	{
		if (dquote)
		{
			if (ft_strchr(str, '\"') == NULL)
				err_handler("unclosed quote"); // clear all memory
			get_next_str_len(&str, &len, '\"');
			dquote = 0;
		}
		else if (squote)
		{
			if (ft_strchr(str, '\'') == NULL)
				err_handler("unclosed quote"); // clear all memory
			get_next_str_len(&str, &len, '\'');
			squote = 0;
		}
		else if (ft_strchr(str, ' ') != NULL
			&& ft_strchr(str, ' ') < ft_strchr(str, '\'')
			&& ft_strchr(str, ' ') < ft_strchr(str, '\"'))
			get_next_str_len(&str, &len, ' ');
		else if (ft_strchr(str, '\"') != NULL
			&& ft_strchr(str, '\"') < ft_strchr(str, '\'')
			&& ft_strchr(str, '\"') < ft_strchr(str, ' '))
		{
			get_next_str_len(&str, &len, '\"');
			dquote = 1;
		}
		else if (ft_strchr(str, '\'') != NULL
			&& ft_strchr(str, '\'') < ft_strchr(str, '\"')
			&& ft_strchr(str, '\'') < ft_strchr(str, ' '))
		{
			get_next_str_len(&str, &len, '\'');
			squote = 1;
		}
		token = (char *)ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(token, str, len + 1);
	}
}

void	check_for_quotes(void)
{
	bool	singleq;
	bool	doubleq;

	singleq = false;
	doubleq = false;
	if (ft_ischrinset(g_mini.input, SINGLEQ))
		singleq = true;
	if (ft_ischrinset(g_mini.input, DOUBLEQ))
		doubleq = true;
	if (singleq || doubleq)
	{
		g_mini.argv = quote_split(g_mini.input, singleq, doubleq);
		if (!g_mini.argv)
			return ;
	}
	else
	{
		g_mini.argv = ft_split(g_mini.input, ' ');
		if (!g_mini.argv)
			return ;
	}
}
