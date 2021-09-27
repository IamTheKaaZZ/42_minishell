/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 16:33:35 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:59:39 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

t_ll	ft_recursive_factorial(t_ll nb)
{
	if (nb == 0)
		return (1);
	return (nb * ft_recursive_factorial(nb - 1));
}
