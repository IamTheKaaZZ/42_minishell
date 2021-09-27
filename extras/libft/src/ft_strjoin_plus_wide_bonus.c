/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_plus_wide_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:09:00 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:01:20 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

char	*ft_strjoin_plus_wide(const char *s1, const wchar_t *s2)
{
	char	*join;
	size_t	i;
	size_t	size;

	if (!s1)
		size = ft_wstrlen(s2) + 1;
	else if (!s2)
		size = ft_strlen(s1) + 1;
	else
		size = ft_strlen(s1) + ft_wstrlen(s2) + 1;
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
