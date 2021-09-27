/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ulong_fd_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:49:35 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:58:04 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

static char	ul_to_char(t_ul toconvert)
{
	char	c;

	c = toconvert % 10;
	c += 48;
	return (c);
}

void	ft_putnbr_ulong_fd(t_ul n, int fd)
{
	if (n != ULONG_MAX)
	{
		if (n < 10)
		{
			ft_putchar_fd(ul_to_char(n), fd);
		}
		if (n >= 10)
		{
			ft_putnbr_ulong_fd(n / 10, fd);
			ft_putchar_fd(ul_to_char(n), fd);
		}
	}
	else
	{
		ft_putstr_fd("18446744073709551615", fd);
	}
}
