/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_long_fd_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:51:09 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:57:43 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

static char	long_to_char(long toconvert)
{
	char	c;

	c = toconvert % 10;
	c += 48;
	return (c);
}

void	ft_putnbr_long_fd(long n, int fd)
{
	if (n != LONG_MIN)
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = -n;
		}
		if (n < 10)
		{
			ft_putchar_fd(long_to_char(n), fd);
		}
		if (n >= 10)
		{
			ft_putnbr_long_fd(n / 10, fd);
			ft_putchar_fd(long_to_char(n), fd);
		}
	}
	else
	{
		ft_putstr_fd("−9223372036854775808", fd);
	}
}
