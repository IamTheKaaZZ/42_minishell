/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:29:42 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:02:56 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**Check if char c is uppercase
*/

static int	ft_isupper(int c)
{
	if (c > 64 && c < 91)
		return (1);
	return (0);
}

/*
**Checks if char c is uppercase, then converts it to lowercase
*/

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c + 32);
	return (c);
}
