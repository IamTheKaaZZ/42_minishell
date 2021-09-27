/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_32bit_str_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:19:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:48:35 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

/*
**	Helper function to handle the edge case of INT32_MIN
**	1. Fill 31/32 bits with 0's
**		Set the signed bit to 1 and NULL-term the string
**	2. Reverse the index order with ft_str_rev
**	RETURN the finished string
*/

static char	*handle_negmax(char *str, size_t bindigits)
{
	size_t	i;

	bindigits = 31;
	i = 0;
	while (bindigits--)
		str[i++] = '0';
	str[i++] = '1';
	str[i] = '\0';
	ft_str_rev(str);
	return (str);
}

/*
**	Helper function to convert if no previous conversion happened AKA i = 0
**	1. Check for negative input
**		- Update negflag to 1 for main function
**		- Set the input to its absolute value
**	2. Fill the string with the 2 modulus of the input
**		- Divide by 2 until input is zero
*/

static void	handle_indexzero(int input, int *negflag, char **str, int i)
{
	if (input < 0)
	{
		*negflag = 1;
		input = ft_abs(input);
	}
	while (input > 0)
	{
		(*str)[i++] = (input % 2) + '0';
		input /= 2;
	}
}

/*
**	Main function:
**	PARAMS:
**	[str]		: 32 bit binary string to return
**	[input]		: input number to convert to binary string
**	[negflag]	: Optional flag for a negative number representation
**	[i]			: Index of where to start adding to the string
**	FUNCTION:
**		1. Edge case check for INT32_MIN
**			=> RETURN: @handle_negmax
**		2. If starting index = 0 AKA clean string
**			=> CONVERT input with @handle_indexzero
**		3. Fill remaining empty bits with 0's + NULL-term the string
**		4. Check negflag for negative representation
**			=> @ft_bin2compl_str
**		5. Reverse index order with ft_str_rev
**	=> RETURN the 32 bit string [str]
*/

char	*ft_bin_32bit_str(char *str, int input, int negflag, int i)
{
	size_t	bindigits;

	bindigits = 0;
	if (input == INT32_MIN)
		return (handle_negmax(str, bindigits));
	if (i == 0)
		handle_indexzero(input, &negflag, &str, i);
	if (ft_strlen(str) < 32)
	{
		bindigits = 32 - ft_strlen(str);
		while (bindigits--)
			str[i++] = '0';
	}
	str[i] = '\0';
	if (negflag)
		str = ft_bin2compl_str(str, i);
	ft_str_rev(str);
	return (str);
}
