/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:06:57 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:00:45 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**	Copies src to dest incl null term
*/

char	*ft_strcpy(char *dest, char *src)
{
	int		len;
	int		i;

	len = ft_strlen(src);
	i = 0;
	while (i < len + 1)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
