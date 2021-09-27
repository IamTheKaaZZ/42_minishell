/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ischarinset_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:59:12 by bcosters          #+#    #+#             */
/*   Updated: 2021/03/01 17:08:58 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**checks if char c is part of the string set
*/

int	ft_ischrinset(char const *set, int c)
{
	while (*set)
	{
		if (*set == (unsigned char)c)
			return (1);
		set++;
	}
	return (0);
}
