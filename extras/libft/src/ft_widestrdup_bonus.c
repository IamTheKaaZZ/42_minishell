/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_widestrdup_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:40:41 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:04:06 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

wchar_t	*ft_widestrdup(const wchar_t *s)
{
	size_t	size;
	wchar_t	*dup;

	size = ft_wstrlen(s) + 1;
	dup = (wchar_t *)malloc(size * sizeof(wchar_t));
	if (!(dup))
		return (NULL);
	return ((wchar_t *)ft_memcpy(dup, s, size));
}
