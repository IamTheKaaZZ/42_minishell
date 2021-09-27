/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_realloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:13:02 by bcosters          #+#    #+#             */
/*   Updated: 2021/06/23 12:46:15 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

/*
**	ft_strjoin but you realloc the joined string, so s1 gets free'd
**	USAGE: s1 = ft_strjoin_realloc(s1, s2);
**	=> This will overwrite the memory of s1
**		=> therefore free its previous memory
*/

char	*ft_strjoin_realloc(char *s1, const char *s2)
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
