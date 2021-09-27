/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin2compl_str_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 12:13:04 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:50:09 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

/*
**	Helper function to handle negative numbers:
**	1. Finds the signed 1's complement of the binary string
**		=> Flips all the bits
**	2. Finds the signed 2's complement of the 1's complement
**		=> Adds the binary number 1 to the 1's complement
**		=> Needed for an accurate representation of the neg number
*/

char	*ft_bin2compl_str(char *str, int i)
{
	size_t	twocompl;

	twocompl = 1;
	i--;
	while (i >= 0)
	{
		if (str[i] == '1')
			str[i--] = '0';
		else
			str[i--] = '1';
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '1' && twocompl == 1)
			str[i] = '0';
		else if (str[i] == '0' && twocompl == 1)
		{
			str[i] = '1';
			twocompl = 0;
		}
		i++;
	}
	return (str);
}
