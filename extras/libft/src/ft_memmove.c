/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:01:41 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:56:31 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**copies n bytes from memory area src to memory area dest.*
**Takes overlap into account by copying backwards (see else)*
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*ts;
	char	*td;
	char	*ends;
	char	*endd;

	if (!dest && !src)
		return (0);
	ts = (char *)src;
	td = (char *)dest;
	if (td < ts)
	{
		while (n--)
			*td++ = *ts++;
	}
	else
	{
		ends = ts + n - 1;
		endd = td + n - 1;
		while (n--)
			*endd-- = *ends--;
	}
	return (dest);
}
