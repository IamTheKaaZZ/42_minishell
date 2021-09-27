/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:38 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:56:10 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**Compares first n bytes of memory str1 and str2*
**Returns 0 if equal, -1 if (1 < 2), 1 if (1 > 2)*
*/

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char	*s1;
	const unsigned char	*s2;

	s1 = (const unsigned char *)str1;
	s2 = (const unsigned char *)str2;
	while (n > 0)
	{
		if ((const unsigned char)*s1++ != (const unsigned char)*s2++)
			return (*--s1 - *--s2);
		n--;
	}
	return (0);
}
