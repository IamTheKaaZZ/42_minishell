/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:21:34 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:01:44 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**appends the NUL-terminated string src to the end of dst.*
**It will append at most (size - strlen(dst) - 1) bytes,*
**NUL-terminating the result.*
*/

size_t	ft_strlcat(char *dest, const char *src, size_t dsize)
{
	char		*d;
	const char	*s;
	size_t		lend;
	size_t		n;

	d = dest;
	s = src;
	n = dsize;
	while (n-- != 0 && *d)
		d++;
	lend = d - dest;
	n = dsize - lend;
	if (n == 0)
		return (lend + ft_strlen(s));
	while (*s)
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (lend + (s - src));
}
