/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modf_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 11:55:25 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:56:47 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

typedef union u_fl
{
	double		fract;
	uint64_t	ipart;
}				t_ufl;

static double	no_fraction(t_ufl *u, double x, double *iptr, int e)
{
	*iptr = x;
	if (e == 0x400 && (u->ipart << 12) != 0)
		return (x);
	u->ipart &= 1ULL << 63;
	return (u->fract);
}

static double	no_ipart(t_ufl *u, double x, double *iptr)
{
	u->ipart &= 1ULL << 63;
	*iptr = u->fract;
	return (x);
}

double	ft_modf(double x, double *iptr)
{
	t_ull	mask;
	int		e;
	t_ufl	u;

	u.fract = x;
	e = (int)(u.ipart >> 52 & 0x7ff) - 0x3ff;
	if (e >= 52)
		return (no_fraction(&u, x, iptr, e));
	if (e < 0)
		return (no_ipart(&u, x, iptr));
	mask = -1ULL >> 12 >> e;
	if ((u.ipart & mask) == 0)
	{
		*iptr = x;
		u.ipart &= 1ULL << 63;
		return (u.fract);
	}
	u.ipart &= ~mask;
	*iptr = u.fract;
	return (x - u.fract);
}
