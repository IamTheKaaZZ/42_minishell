/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_widechar_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:33:35 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:01:31 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

char	*ft_strjoin_widechar(const char *s1, wchar_t c)
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
	join[i++] = (char)c;
	join[i] = '\0';
	return (join);
}
