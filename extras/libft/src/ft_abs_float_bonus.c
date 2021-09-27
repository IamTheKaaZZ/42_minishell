/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_float_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:01:33 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:44:03 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

double	ft_abs_float(double x)
{
	if (ft_isinf(x))
		return (1.0 / 0.0);
	if (x == -0 || x == 0)
		return (0);
	if (x < 0)
		return (-x);
	return (x);
}
