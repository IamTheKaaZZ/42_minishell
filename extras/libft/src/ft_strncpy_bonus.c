/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:55:34 by bcosters          #+#    #+#             */
/*   Updated: 2021/02/28 17:11:42 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Copy at most len/n amount of bytes from src to dest
**	if src < n bytes, the rest is filled with nulls in dest
*/

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
