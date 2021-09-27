/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:32:10 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:57:27 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	int_to_char(int toconvert)
{
	char	c;

	c = toconvert % 10;
	c += 48;
	return (c);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n != -2147483648)
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = -n;
		}
		if (n < 10)
		{
			ft_putchar_fd(int_to_char(n), fd);
		}
		if (n >= 10)
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putchar_fd(int_to_char(n), fd);
		}
	}
	else
	{
		ft_putstr_fd("-2147483648", fd);
	}
}
