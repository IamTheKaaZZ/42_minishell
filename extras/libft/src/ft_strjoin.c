/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 11:41:18 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:01:38 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**Allocates (with malloc(3)) and returns a new string,*
**which is the result of the concatenation of ’s1’ and ’s2’.*
*/

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*join;
	size_t	i;
	size_t	size;

	if (!s1)
		size = ft_strlen(s2) + 1;
	else if (!s2)
		size = ft_strlen(s1) + 1;
	else
		size = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)malloc(size * sizeof(char));
	if (!(join))
		return (NULL);
	i = 0;
	while (s1 && *s1)
		join[i++] = *s1++;
	while (s2 && *s2)
		join[i++] = *s2++;
	join[i] = '\0';
	return (join);
}
