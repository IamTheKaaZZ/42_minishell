/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:49:03 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/07 12:15:52 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/*
**returns the index to the first occurrence of the character c in the string s*
*/

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
		if (*(temp + i + 1) != 0 && *(temp + i) == '\\')
		{
			i += 2;
			continue ;
		}
		if (*(temp + i) == (unsigned char)c)
			return (i);
		i++;
	}
	return (INT_MAX);
}

bool	str_contains_chars(const char *str, char *charset)
{
	int	i;

	if (!str || !charset)
		return (false);
	i = -1;
	while (charset[++i])
		if (ft_ischrinset(str, charset[i]))
			return (true);
	return (false);
}

bool	char_before_others(const char *str, char c, char *charset)
{
	int	i;

	if (!str || !charset)
		return (false);
	i = -1;
	while (charset[++i])
		if (strchr_index(str, c) > strchr_index(str, charset[i]))
			return (false);
	return (true);
}
