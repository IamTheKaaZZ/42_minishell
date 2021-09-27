/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispunct_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:13:07 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/27 10:47:19 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

bool	ft_ispunct(int c)
{
	if (ft_isprint(c) && !ft_isalnum(c) && c != ' ')
		return (1);
	else
		return (0);
}
