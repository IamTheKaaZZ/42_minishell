/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bankers_round_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:56:52 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:45:05 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

static double	precision_zero(double absfract, double ipart, double x)
{
	if (absfract < 0.5)
		return (ipart);
	else
	{
		if (x < 0)
			return (ipart - 1);
		else
			return (ipart + 1);
	}
}

static	double	float_in_range(double x, double ipart, double absf, int prec)
{
	if (ipart - absf != 0 || (t_ll)ipart % 2 == 0)
	{
		if (x < 0 && absf >= 0.5)
			ipart = (ipart - 1);
		else if (x > 0 && absf >= 0.5)
			ipart = (ipart + 1);
		ipart /= ft_iterative_power(10, prec);
		return (ipart);
	}
	return (x);
}

static double	check_sign(double x, double rounding)
{
	if (x < 0)
		return (x - rounding);
	else
		return (x + rounding);
}

double	ft_bankers_round(double x, int precision)
{
	double	ipart;
	double	fract;
	double	absfract;
	double	rounding;

	ipart = 0;
	rounding = x * ft_iterative_power(10, precision);
	fract = ft_modf(rounding, &ipart);
	absfract = ft_abs_float(fract);
	if (precision == 0)
		return (precision_zero(absfract, ipart, x));
	if (precision > 6 || absfract == 0)
	{
		fract = ft_modf(x, &ipart);
		absfract = ft_abs_float(fract);
		rounding = 0.5 / ft_iterative_power(10, precision);
		if (absfract != 0 && (absfract - rounding != 0 || (t_ll)ipart % 2 == 0))
			return (check_sign(x, rounding));
	}
	if (absfract != 0)
		return (float_in_range(x, ipart, absfract, precision));
	return (x);
}
