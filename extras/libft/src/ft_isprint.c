/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:21:32 by bcosters          #+#    #+#             */
/*   Updated: 2021/02/16 10:02:41 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**Checks if char c is a printable ASCII char*
** DEL is not printable, i blame the internet
*/

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}
