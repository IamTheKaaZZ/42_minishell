/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:30:22 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:02:33 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**returns a pointer to the last occurrence of the character c in the string s*
*/

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*temp;

	temp = (char *)str;
	if ((unsigned char)c == 0)
		return (temp + ft_strlen(temp));
	i = ft_strlen(temp) - 1;
	while (i >= 0)
	{
		if (*(temp + i) == (unsigned char)c)
			return (temp + i);
		i--;
	}
	return (0);
}
