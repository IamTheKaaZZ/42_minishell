/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:07:06 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:59:33 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

void	*ft_realloc(char *oldptr, char *newptr, size_t oldsize, size_t newsize)
{
	if (newsize == 0)
	{
		free(oldptr);
		oldptr = NULL;
		return (NULL);
	}
	else if (!oldptr)
		return (malloc(newsize));
	else if (newsize <= oldsize)
		return (oldptr);
	else
	{
		if (!((oldptr) && (newsize > oldsize)))
			return (NULL);
		newptr = malloc(newsize);
		if (!(newptr))
			return (NULL);
		free(oldptr);
		oldptr = NULL;
		return (newptr);
	}
}
