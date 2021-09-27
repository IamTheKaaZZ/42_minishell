/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:26:11 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:03:03 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**Checks if char c is lowercase*
*/

static int	ft_islower(int c)
{
	if (c > 96 && c < 123)
		return (1);
	return (0);
}

/*
**Checks if char c is lowercase then converts it to uppercase*
*/

int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (c - 32);
	return (c);
}
