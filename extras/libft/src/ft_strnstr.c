/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:02:27 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:02:26 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**replaces a huge recurring code block in the main funstion
**		strc = *str++;
**		if (strc == '\0' || n-- < 1)
**			return (NULL);
**		while (strc != c)
**		{
**			strc = *str++;
**			if (strc == '\0' || n-- < 1)
**				return (NULL);
**		}
**		if (lenpat > n)
**			return (NULL);
*/

static int	pointermagic(char const *str, size_t n, char c, size_t l)
{
	char	strc;

	strc = *str;
	if (strc == '\0' || n < 1)
		return (0);
	while (strc != c)
	{
		strc = *str++;
		if (strc == '\0' || n-- < 1)
			return (0);
	}
	if (l > n)
		return (0);
	return (1);
}

/*
**finds the first occurrence of the substring patt in the string str.*
**only checks the first n bytes of str for a match with patt.*
*/

char	*ft_strnstr(const char *str, const char *patt, size_t n)
{
	char	c;

	if (ft_strlen(patt) == 1)
	{
		if (ft_strchr(str, patt[0]) <= str + n - 1 || n > ft_strlen(str))
			return (ft_strchr(str, patt[0]));
		else
			return (NULL);
	}
	c = *patt++;
	if (c != '\0')
	{
		if (pointermagic(str++, n--, c, ft_strlen(patt)) == 0)
			return (NULL);
		while (ft_strncmp(str, patt, ft_strlen(patt)) != 0)
		{
			if (pointermagic(str++, n--, c, ft_strlen(patt)) == 0)
				return (NULL);
		}
		if (ft_strlen(patt) > 1)
			str--;
	}
	return ((char *)str);
}
