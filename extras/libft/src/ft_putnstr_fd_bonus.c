/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:01:17 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:58:38 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

void	ft_putnstr_fd(char *s, size_t n, int fd)
{
	while (*s && n--)
		ft_putchar_fd(*s++, fd);
}
