/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:30:06 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/11 14:34:18 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**Returns the amount of chars of a string before the NUL-term*
*/

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (*str++)
		i++;
	return (i);
}
