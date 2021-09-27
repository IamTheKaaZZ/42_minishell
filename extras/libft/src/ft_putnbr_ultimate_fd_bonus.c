/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ultimate_fd_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:57:34 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:58:24 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

void	ft_putnbr_ultimate_fd(t_ll n, int fd)
{
	if ((t_ul)n == ULONG_MAX)
		ft_putnbr_ulong_fd((t_ul)n, fd);
	else
		ft_putnbr_long_fd(n, fd);
}
