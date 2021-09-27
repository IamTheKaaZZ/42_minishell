/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:18:26 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:02:20 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	size;
	char	*dup;

	if (n < ft_strlen(s))
		size = n + 1;
	else
		size = ft_strlen(s) + 1;
	dup = (char *)ft_calloc(size, sizeof(char));
	if (!(dup))
		return (NULL);
	ft_memcpy(dup, s, size);
	if (dup[n] != '\0')
		dup[n] = '\0';
	return (dup);
}
