/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:23:19 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:51:13 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

int	ft_floor_int(double x)
{
	int	i;

	i = x - 2;
	while (i <= x - 1)
		i++;
	return (i);
}

t_ll	ft_floor_ll(double x)
{
	t_ll	i;

	i = x - 2;
	while (i <= x - 1)
		i++;
	return (i);
}

double	ft_floor(double x)
{
	double	ipart;
	double	fraction;

	ipart = 0;
	fraction = ft_modf(x, &ipart);
	if (fraction == 0)
		return (x);
	else if (x < 0 && fraction > -1)
		return (ipart - 1);
	else
		return (ipart);
}
