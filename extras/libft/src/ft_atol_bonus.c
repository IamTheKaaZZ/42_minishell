/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:08:50 by bcosters          #+#    #+#             */
/*   Updated: 2021/05/25 16:09:57 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

/*
**Function to convert a string to a number, including negatives*
**only converts if first two chars are - and a digit or digits*
*/

long	ft_atol(const char *numstr)
{
	int		i;
	long	res;
	int		sign;

	while (ft_isspace(*numstr))
		numstr++;
	i = 0;
	res = 0;
	sign = 1;
	if (*numstr == '-')
	{
		sign = -1;
		i++;
	}
	if (*numstr == '+')
		i++;
	while (*(numstr + i))
	{
		if (!ft_isdigit(numstr[i]))
			break ;
		res = res * 10 + numstr[i] - '0';
		i++;
	}
	return (res * sign);
}
