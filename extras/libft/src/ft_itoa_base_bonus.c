/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:48:54 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:53:40 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

/*
**	Function that returns an allocated string of the int converted to basestr
**	-> temp is malloced with size 42 so it is definitely big enough
**	-> result gets malloced with the exact size needed
**		=> ft_str_realloc (free and NULLs temp)
**	RETURN: result string with exact good size!
*/

char	*ft_itoa_base(int n, char *basestr)
{
	char	*temp;
	char	*result;

	temp = malloc(42 * sizeof(char));
	if (!(temp))
		return (NULL);
	temp = ft_int_to_base(temp, basestr, n);
	result = ft_str_realloc(temp, ft_strlen(temp));
	return (result);
}
