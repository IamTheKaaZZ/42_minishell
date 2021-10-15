/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:07:45 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/11 14:41:02 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**returns a pointer to a new string which is a duplicate of the string s.*
**Memory for the new string is obtained with malloc(3),*
**and can be freed with free(3)*
*/

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*dup;

	if (!s)
		return (NULL);
	size = ft_strlen(s) + 1;
	dup = (char *)malloc(size * sizeof(char));
	if (!(dup))
		return (NULL);
	return ((char *)ft_memcpy(dup, s, size));
}
