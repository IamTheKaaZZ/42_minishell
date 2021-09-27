/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_roundf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 09:59:41 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:59:59 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

double	ft_roundf(double nb, int decimals)
{
	double	power;

	if (decimals <= 0)
		return (nb);
	power = ft_iterative_power(10, decimals);
	nb *= power;
	if (nb >= 0)
		return ((t_ll)(nb + 0.5) / power);
	else
		return ((t_ll)(nb - 0.5) / power);
}
