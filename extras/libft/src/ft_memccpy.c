/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:11:17 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:55:55 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**copies no more than n bytes from memory area src to memory area dest,*
**stopping when the character c is copied, then returns pointer to next byte.*
**result is undefined if memories overlap*
*/

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*tdest;
	const unsigned char	*tsrc;
	size_t				check;

	tdest = (unsigned char *)dest;
	tsrc = (const unsigned char *)src;
	check = 0;
	while (n--)
	{
		if (*tsrc == (unsigned char)c)
		{
			*tdest = (unsigned char)c;
			check = 1;
			break ;
		}
		*tdest++ = *tsrc++;
	}
	if (check)
		return ((void *)tdest + 1);
	else
		return (0);
}
