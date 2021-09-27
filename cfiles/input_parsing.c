/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:12:04 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/22 11:56:44 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

bool	count_quotes(const char *str)
{
	int		sqoutes;
	int		dquotes;
	int		i;
	int		j;
	char	buf[4096];

	sqoutes = 0;
	dquotes = 0;
	ft_bzero(buf, 4096);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == SINGLEQ)
		{
			sqoutes++;
			buf[j] = 's';
			j++;
		}
		if (str[i] == DOUBLEQ)
		{
			dquotes++;
			buf[j] = 'd';
			j++;
		}
	}
	if (dquotes % 2 != 0 && sqoutes % 2 != 0)
	{
		errno = EPERM;
		err_handler("Unclosed quotes");
		return (0);
	}
	if (dquotes % 2 != 0)
	{
		printf("odd number of double quotes\n");
		//check for sds in buf -> case where it is still OK
	}
	if (sqoutes % 2 != 0)
	{
		printf("odd number of single quotes\n");
		//check for dsd in buf -> case where it is still OK
	}
	printf("buffer = %s\n", buf);
	return (0);
}

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
