/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:25:51 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:02:12 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**only compares the first (at most) n bytes of s1 and s2.*
**returns an integer (ASCII dec) less than, equal to, or greater than zero*
**if s1 is respectively, less than, to match, greater than s2.*
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	res;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if ((unsigned char)s2[i] == 0)
			return ((unsigned char)s1[i]);
		if ((unsigned char)s1[i] == 0)
			return (-(unsigned char)s2[i]);
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			res = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (res);
		}
		i++;
	}
	return (0);
}
