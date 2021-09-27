/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ui_fd_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:49:46 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:57:54 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

static char	ui_to_char(t_ui toconvert)
{
	char	c;

	c = toconvert % 10;
	c += 48;
	return (c);
}

void	ft_putnbr_ui_fd(t_ui n, int fd)
{
	if (n != UINT32_MAX)
	{
		if (n < 10)
		{
			ft_putchar_fd(ui_to_char(n), fd);
		}
		if (n >= 10)
		{
			ft_putnbr_ui_fd(n / 10, fd);
			ft_putchar_fd(ui_to_char(n), fd);
		}
	}
	else
	{
		ft_putstr_fd("4294967295", fd);
	}
}
