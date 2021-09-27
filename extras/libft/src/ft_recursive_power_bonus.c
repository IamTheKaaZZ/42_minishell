/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 19:25:45 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:59:53 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

t_ll	ft_recursive_power(t_ll nb, t_ll power)
{
	if (nb == 0 && power == 0)
		return (1);
	if (power != 0)
		return (nb * ft_recursive_power(nb, (power - 1)));
	else
		return (1);
}
