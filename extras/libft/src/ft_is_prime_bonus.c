/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 17:59:18 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:52:05 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

t_ull	ft_is_prime(t_ull nb)
{
	t_ull	temp;
	t_ull	i;

	if (nb == 0 || nb == 1)
		return (0);
	temp = nb / 2;
	i = 2;
	while (i <= temp)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}
