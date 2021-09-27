/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 16:04:35 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:53:21 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

t_ll	ft_iterative_factorial(t_ll nb)
{
	t_ll	i;
	t_ll	f;

	i = 1;
	f = 1;
	while (i <= nb)
	{
		f *= i;
		i++;
	}
	return (f);
}
