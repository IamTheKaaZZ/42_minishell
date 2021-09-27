/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 22:43:32 by bcosters          #+#    #+#             */
/*   Updated: 2021/06/03 14:12:55 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

static t_ul	fib(t_ul n)
{
	if (n == 0)
		return (0);
	else if (n == 1)
		return (1);
	else
	{
		return (fib(n - 1) + fib(n - 2));
	}
}

t_ull	ft_fibonacci(t_ll index)
{
	if (index < 0)
		return (-1);
	return (fib(index));
}
