/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 11:02:23 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:02:48 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**Allocates (with malloc(3)) and returns a substring from the string ’s’.*
**The substring begins at index ’start’ and is of maximum size ’len’.*
*/

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		size = ft_strlen(s) + 1;
	else
		size = len + 1;
	sub = (char *)ft_calloc(size, sizeof(char));
	if (!(sub))
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
		return (sub);
	i = 0;
	while (*(s + start) && i < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
