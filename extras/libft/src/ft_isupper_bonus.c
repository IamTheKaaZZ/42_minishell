/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isupper_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:58:15 by bcosters          #+#    #+#             */
/*   Updated: 2021/02/15 16:20:56 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**Check if char c is uppercase*
*/

int	ft_isupper(int c)
{
	if (c > 64 && c < 91)
		return (1);
	return (0);
}
