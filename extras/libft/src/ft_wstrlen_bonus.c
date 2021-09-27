/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:27:20 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:04:35 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

size_t	ft_wstrlen(const wchar_t *wide_str)
{
	size_t	len;

	len = 0;
	while (*wide_str)
	{
		len++;
		wide_str++;
	}
	return (len);
}
