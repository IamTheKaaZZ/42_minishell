/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:12:04 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/21 15:37:14 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

/*
 * Handle cases:
	"'$SOMETHING'" => 'expanded'
	'"$SOMETHING"' => "$SOMETHING"
*/

char	**quote_split(const char *str, bool sq, bool dq)
{
	if (sq && dq)
	{

	}
	else if (sq)
	{

	}
	else if (dq)
	{

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
		g_mini.argv = quote_split(g_mini.input, singleq, doubleq);
	else
		g_mini.argv = ft_split(g_mini.input, ' ');
}

void	parsed_chars(char *parsed_instruction)
{
	if (ft_strequal(parsed_instruction, "<"))
		//open next arg as inputfile
	else if (ft_strequal(parsed_instruction, "<<"))
		//here_doc start for the previous command (arg)
	else if (ft_strequal(parsed_instruction, ">"))
		//redirect output into (created) file (O_TRUNC)
	else if (ft_strequal(parsed_instruction, ">>"))
		//redirect output into (created) file (O_APPEND)
	else if (ft_strequal(parsed_instruction, "|"))
		//pipe output of previous command into next one
}
