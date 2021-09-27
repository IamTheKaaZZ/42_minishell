/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:11:56 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:53:48 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

/*
**	1.	malloc is big enough for a 32 bit int (10 + 2)
**	2.	result points to the ending null
**	3.	deal with n == 0
**	4.	deal with n == INT_MIN
**	5.	deal with n < 0
**	6.	rest is when n is pos
*/

char	*ft_itoa(int n)
{
	char	*temp;
	char	*result;

	temp = malloc(42 * sizeof(char));
	if (!(temp))
		return (NULL);
	temp = ft_int_to_base(temp, B_DEFAULT, n);
	result = ft_str_realloc(temp, ft_strlen(temp));
	return (result);
}
