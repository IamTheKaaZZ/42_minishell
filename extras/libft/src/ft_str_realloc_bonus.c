/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_realloc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:42:24 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:00:20 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

char	*ft_str_realloc(char *oldptr, size_t newlen)
{
	size_t	newsize;
	char	*newptr;

	newsize = newlen + 1;
	newptr = ft_calloc(newsize, sizeof(char));
	if (!(newptr))
		return (NULL);
	ft_strlcpy(newptr, oldptr, (ft_strlen(oldptr) + 1));
	ft_strdel(&oldptr);
	return (newptr);
}
