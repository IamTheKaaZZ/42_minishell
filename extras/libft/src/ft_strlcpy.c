/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:51:56 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:01:52 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**copies up to size - 1 characters from the NUL-terminated string src to dst,*
**NUL-terminating the result. *
**	OLD FUNCTION:
**	size_t	i;
**
**	i = 0;
**	if (size > 0)
**	{
**		while (*(src + i))
**		{
**			if (i == size - 1)
**				break ;
**			*(dest + i) = *(src + i);
**			i++;
**		}
**		*(dest + i) = 0;
**	}
**	return (ft_strlen(src));
*/

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	slen;

	if (!dest && !src)
		return (0);
	slen = ft_strlen(src);
	if (slen + 1 < size)
		ft_memcpy(dest, src, slen + 1);
	else if (size != 0)
	{
		ft_memcpy(dest, src, size - 1);
		dest[size - 1] = '\0';
	}
	return (slen);
}
