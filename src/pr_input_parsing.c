/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_input_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:12:04 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/08 17:04:49 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

static void	combine_args(t_node **list, char **token, char **joined, bool sp)
{
	char	*temp;

	if (sp == false)
	{
		temp = *joined;
		*joined = ft_strjoin(temp, *token);
		ft_strdel(&temp);
		ft_strdel(token);
	}
	if (sp == true)
	{
		if (*joined != NULL)
		{
			add_to_tail(list, new_node(*joined));
			*joined = NULL;
		}
		temp = *joined;
		*joined = ft_strjoin(temp, *token);
		ft_strdel(&temp);
		ft_strdel(token);
	}
}

static bool	init_split(const char *str, size_t *len, char **joined)
{
	if (!str)
		return (false);
	*len = 0;
	*joined = NULL;
	while (*str && *str == ' ')
		str++;
	return (true);
}

/*
 * Handle cases:
	"'$SOMETHING'" => 'expanded'
	'"$SOMETHING"' => "$SOMETHING"
*/

void	split_input(t_node **parsed_list, const char *str, t_prbools *b)
{
	size_t	len;
	char	*token;
	char	*joined;

	if (!init_split(str, &len, &joined))
		return ;
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
		token = process_token(str, &len, b);
		combine_args(parsed_list, &token, &joined, b->space_found);
		str += len;
	}
	if (joined != NULL)
		add_to_tail(parsed_list, new_node(joined));
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
