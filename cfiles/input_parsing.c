/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:12:04 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/27 10:32:10 by bcosters         ###   ########.fr       */
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
	char	**temp_dq;
	// char	**temp_sq;
	// int		doublequote;
	// int		singlequote;

	if (!count_quotes(str))
		return (NULL);
	if (sq && dq)
	{

	}
	else if (sq)
	{

	}
	else if (dq)
	{
		temp_dq = ft_split(str, '\"');
	}
	return (NULL);
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
