/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:40:53 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 17:00:08 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**	Helper function to get the arraysize
**	returns size 1 when c is not found in s
*/

static size_t	get_arrsize(char const *s, char c)
{
	size_t	size;
	size_t	len;

	if (*s == 0)
		return (1);
	len = 0;
	size = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (len != 0)
				size++;
			len = 0;
		}
		else
			len++;
		s++;
	}
	if (len != 0)
		size += 2;
	else
		size++;
	return (size);
}

/*
**	Iteratively finds the next string and corresponding lenght*
**	Every time this gets called.
*/

static void	get_next_str_len(char const **str, size_t *len, char c)
{
	size_t	i;

	*str += *len;
	*len = 0;
	i = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return ;
		(*len)++;
		i++;
	}
}

/*
**	Panic dump all the memory allocated*
*/

static char	**ft_malloc_fail(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

/*
**	1. Protect the function for case s == NULL
**	2. Get the array size with the helper function
**	3. Calloc the array (fill with nulls) and check for fails
**	4. Use the next_str_len function to find next str and length
**	5. Calloc the found string, check for fails and add it with strlcpy
**		5.1	if anything goes wrong --> panic dump with ft_malloc_fail
**	6. terminating NULL is the last elem automatically and return
*/

char	**ft_split(char const *s, char c)
{
	char	**arrsplit;
	size_t	len;
	size_t	i;
	size_t	arrsize;

	if (!s)
		return (NULL);
	arrsize = get_arrsize(s, c);
	arrsplit = (char **)ft_calloc(arrsize, sizeof(char *));
	if (!(arrsplit))
		return (NULL);
	i = 0;
	len = 0;
	while (i < arrsize - 1)
	{
		get_next_str_len(&s, &len, c);
		arrsplit[i] = (char *)ft_calloc((len + 1), sizeof(char));
		if (!(arrsplit[i]))
			return (ft_malloc_fail(arrsplit));
		ft_strlcpy(arrsplit[i], s, len + 1);
		i++;
	}
	return (arrsplit);
}
