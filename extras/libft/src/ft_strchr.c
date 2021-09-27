/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:06:49 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:00:35 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**returns a pointer to the first occurrence of the character c in the string s*
*/

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	char	*temp;

	temp = (char *)str;
	if (c == 0)
		return (temp + ft_strlen(temp));
	i = 0;
	while (*(temp + i))
	{
		if (*(temp + i) == (unsigned char)c)
			return (temp + i);
		i++;
	}
	return (0);
}
