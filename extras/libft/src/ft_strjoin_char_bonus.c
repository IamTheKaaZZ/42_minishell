/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:00:06 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:01:10 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

/*
**Allocates (with malloc(3)) and returns a new string,*
**which is the result of the concatenation of ’s1’ and the char c.*
*/

char	*ft_strjoin_char(const char *s1, char c)
{
	char	*join;
	size_t	i;
	size_t	size;

	if (!s1)
		size = 2;
	else
		size = ft_strlen(s1) + 2;
	join = (char *)malloc(size * sizeof(char));
	if (!(join))
		return (NULL);
	i = 0;
	while (s1 && *s1)
		join[i++] = *s1++;
	join[i++] = c;
	join[i] = '\0';
	return (join);
}
