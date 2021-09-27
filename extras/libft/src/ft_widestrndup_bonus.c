/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_widestrndup_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:43:52 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:04:24 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

wchar_t	*ft_widestrndup(const wchar_t *s, size_t n)
{
	size_t	size;
	wchar_t	*dup;

	if (n < ft_wstrlen(s))
		size = n + 1;
	else
		size = ft_wstrlen(s) + 1;
	dup = (wchar_t *)ft_calloc(size, sizeof(wchar_t));
	if (!(dup))
		return (NULL);
	ft_memcpy(dup, s, (size * sizeof(wchar_t)));
	if (dup[n] != L'\0')
		dup[n] = L'\0';
	return (dup);
}
