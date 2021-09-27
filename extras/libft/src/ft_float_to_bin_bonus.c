/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_to_bin_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:57:57 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:32:39 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

static char	*int_to_bin(long nb, int i, int j, char *bin)
{
	int	k;

	k = i - 1;
	while (k >= 0)
	{
		if ((nb >> k) & 1)
			bin[j] = '1';
		else
			bin[j] = '0';
		j++;
		k--;
	}
	return (bin);
}

char	*ft_float_to_binstr(float f)
{
	char	*binarystr;
	t_float	var;

	binarystr = (char *)malloc(35 * sizeof(char));
	if (!binarystr)
		return (NULL);
	var.f = f;
	binarystr[0] = var.raw.sign + '0';
	binarystr[1] = '|';
	binarystr = int_to_bin(var.raw.exponent, 8, 2, binarystr);
	binarystr[10] = '|';
	binarystr = int_to_bin(var.raw.mantissa, 23, 11, binarystr);
	binarystr[35] = '\0';
	return (binarystr);
}

char	*ft_double_to_binstr(double d)
{
	char		*binarystr;
	t_double	var;

	binarystr = (char *)malloc(67 * sizeof(char));
	if (!binarystr)
		return (NULL);
	var.d = d;
	binarystr[0] = var.raw.sign + '0';
	binarystr[1] = '|';
	binarystr = int_to_bin(var.raw.exponent, 11, 2, binarystr);
	binarystr[13] = '|';
	binarystr = int_to_bin(var.raw.mantissa, 52, 14, binarystr);
	binarystr[67] = '\0';
	return (binarystr);
}
