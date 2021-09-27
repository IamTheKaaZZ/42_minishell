/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_base_from_str_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:28:05 by bcosters          #+#    #+#             */
/*   Updated: 2021/05/24 10:21:02 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

/*
**	Function that returns the base to convert to as a number from a string:
**	1.	No basestr -> default base 10
**	2.	Special cases = 32 or 64 bit signed binary -> still base 2
**	3.	Normal cases = string length of the basestr
*/

size_t	ft_get_base_from_str(char *basestr)
{
	if (!basestr)
		return (10);
	else if (ft_strequal(basestr, B_BIN32))
		return (2);
	else if (ft_strequal(basestr, B_BIN64))
		return (2);
	else if (ft_strequal(basestr, B_BIN128))
		return (2);
	else
		return (ft_strlen(basestr));
}
