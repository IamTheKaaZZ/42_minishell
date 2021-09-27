/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:01:41 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:56:17 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**copies n bytes from memory area src to memory area dest.*
**The memory areas must not overlap.*
**IF there is overlap -> memmove*
*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tdest;
	unsigned char	*tsrc;

	if (!dest && !src)
		return (0);
	tdest = (unsigned char *)dest;
	tsrc = (unsigned char *)src;
	while (n--)
	{
		*tdest++ = *tsrc++;
	}
	return (dest);
}
