/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_to_bin.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:58:13 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:10:47 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FLOAT_TO_BIN_H
# define FT_FLOAT_TO_BIN_H

# include <stdlib.h>

/*
**		// Order is important.
**		// Here the members of the union data structure
**		// use the same memory (32 bits).
**		// The ordering is taken
**		// from the LSB to the MSB.
*/

typedef union u_float
{
	float	f;
	struct s_binf
	{
		unsigned int	mantissa : 23;
		unsigned int	exponent : 8;
		unsigned int	sign : 1;
	} raw;
}	t_float;

char	*ft_float_to_binstr(float f);

/*
**		// Order is important.
**		// Here the members of the union data structure
**		// use the same memory (64 bits).
**		// The ordering is taken
**		// from the LSB to the MSB.
*/

typedef union u_double
{
	double	d;
	struct s_bind
	{
		unsigned long	mantissa : 52;
		unsigned int	exponent : 11;
		unsigned int	sign : 1;
	} raw;
}	t_double;

char	*ft_double_to_binstr(double d);

#endif
