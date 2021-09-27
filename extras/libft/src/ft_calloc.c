/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:30:10 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:50:43 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**Allocates an array of nmemb elements of size in bytes*
** + fills these bytes with zeros (nulls)*
** + has integer overflow protection*
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*resmem;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	resmem = malloc(nmemb * size);
	if ((nmemb * size) > 2147483647 || !(resmem))
		return (NULL);
	resmem = ft_bzero(resmem, nmemb * size);
	return (resmem);
}
