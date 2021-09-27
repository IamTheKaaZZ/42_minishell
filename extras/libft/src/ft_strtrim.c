/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:19:15 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:02:41 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**helper function to check if c is part of set*
*/

static int	ispartofset(char const *set, int c)
{
	int		i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

/*
**helper function to get istart for the trimmed string*
*/

static int	get_istart(char const *str, char const *set)
{
	int	i;

	i = 0;
	while (ispartofset(set, str[i]))
		i++;
	return (i);
}

/*
**helper function to get iend for the trimmed*
*/

static int	get_iend(const char *str, const char *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (ispartofset(set, str[i]))
		i--;
	return (i);
}

/*
**	1. check if s1 exists*
**	2. get the length of the trimmed string using helper fts*
**	3. allocate the memory and check if malloc fails*
**	4. fill trimmed with the contents we want to keep
**	NULL-term is auto added through calloc*
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	i;
	size_t	istart;
	size_t	trimlen;

	if (s1 == NULL)
		return (NULL);
	if (get_iend(s1, set) < 0 || (size_t)get_istart(s1, set) >= ft_strlen(s1))
		trimlen = 0;
	else
		trimlen = get_iend(s1, set) - get_istart(s1, set) + 1;
	trimmed = (char *)ft_calloc((trimlen + 1), sizeof(char));
	if (!(trimmed))
		return (NULL);
	i = 0;
	istart = get_istart(s1, set);
	while (i < trimlen)
		trimmed[i++] = s1[istart++];
	return (trimmed);
}
