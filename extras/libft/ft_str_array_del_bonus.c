/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_array_del_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:39:56 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/17 14:20:50 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Free and NULL an array of strings with the last element being NULL-pointer
*/

void	ft_str_array_del(char ***str_array)
{
	int	i;

	i = -1;
	while ((*str_array)[++i])
		ft_strdel(&(*str_array)[i]);
	*str_array = NULL;
}
