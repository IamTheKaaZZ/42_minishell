/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:17:55 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:03:47 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

/*
**	Function that returns an allocated string of the ulong converted to basestr
**	-> temp is malloced with size 168 so it is definitely big enough
**	-> result gets malloced with the exact size needed
**		=> ft_str_realloc (free and NULLs temp)
**	RETURN: result string with exact good size!
*/

char	*ft_ultoa_base(t_ul n, char *basestr)
{
	char	*temp;
	char	*result;

	temp = malloc(168 * sizeof(char));
	if (!(temp))
		return (NULL);
	temp = ft_ulong_to_base(temp, basestr, n);
	result = ft_str_realloc(temp, ft_strlen(temp));
	return (result);
}
