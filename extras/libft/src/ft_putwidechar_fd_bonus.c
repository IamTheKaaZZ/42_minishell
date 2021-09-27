/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwidechar_fd_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:10:26 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:59:15 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

void	ft_putwidechar_fd(int fd, wchar_t wide_c)
{
	write(fd, &wide_c, sizeof(wchar_t));
}

void	ft_putwidechar(wchar_t wide_c)
{
	ft_putwidechar_fd(1, wide_c);
}

void	ft_putwidestr_fd(int fd, wchar_t *wide_str)
{
	while (*wide_str)
		ft_putwidechar_fd(fd, *wide_str++);
}

void	ft_putwidestr(wchar_t *wide_str)
{
	ft_putwidestr_fd(1, wide_str);
}

void	ft_putwidestr_nl(wchar_t *wide_str)
{
	ft_putwidestr_fd(1, wide_str);
	ft_putchar('\n');
}
