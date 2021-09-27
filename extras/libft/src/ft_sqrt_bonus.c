/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:07:37 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:00:14 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

t_ll	ft_sqrt(t_ll nb)
{
	t_ll	i;
	t_ll	res;

	if (nb == 0 || nb == 1)
		return (nb);
	i = 1;
	res = 1;
	while (res < nb)
	{
		res = i * i;
		i++;
	}
	if (res == nb)
		return (i - 1);
	else
		return (0);
}
