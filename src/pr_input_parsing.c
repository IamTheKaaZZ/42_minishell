/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_input_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:12:04 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/08 11:05:46 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/*
 * Handle cases:
	"'$SOMETHING'" => 'expanded'
	'"$SOMETHING"' => "$SOMETHING"
*/

void	split_input(t_node **parsed_list, const char *str, t_prbools *b)
{
	size_t	len;
	char	*token;

	if (!str)
		return ;
	len = 0;
	while (*str)
	{
		if (!parse_quotes_spaces(&str, &len, b))
		{
			clear_env_list(parsed_list);
			return ;
		}
		if ((len == 0 && !str_contains_chars(str, " \'\"")))
			len = ft_strlen(str);
		if (!*str)
			break ;
		token = process_token(str, &len, &b->dquote, &b->no_quote);
		add_to_tail(parsed_list, new_node(token));
	}
}

bool	parse_input_line(void)
{
	t_node		*parsed_list;
	t_prbools	bools;
	int			i;
	char		error[100];

	parsed_list = NULL;
	ft_bzero(&bools, sizeof(t_prbools));
	split_input(&parsed_list, g_mini.input, &bools);
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
