/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:16:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:52:17 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**Checks if char c is lowercase
*/

static int	ft_islower(int c)
{
	if (c > 96 && c < 123)
		return (1);
	return (0);
}

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
**Checks if char c is a letter
*/

int	ft_isalpha(int c)
{
	if (ft_isupper(c) || ft_islower(c))
		return (1);
	return (0);
}
