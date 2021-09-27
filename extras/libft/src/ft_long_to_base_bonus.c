/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_to_base_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 10:02:13 by bcosters          #+#    #+#             */
/*   Updated: 2021/05/24 10:24:35 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

/*
**	Helper function to identify UC or LC HEX
**	RETURN: The number converted to the appropriate char
*/

static char	reval(long num, char *basestr)
{
	if (num >= 10 && ft_ischrinset(basestr, 'A'))
		return ((char)num - 10 + 'A');
	else if (num >= 10 && ft_ischrinset(basestr, 'a'))
		return ((char)num - 10 + 'a');
	else
		return ((char)num + '0');
}

/*
**	Helper function to handle normal input
**	1. Get the base number from ft_get_base_from_str
**	2. Check for negative input
**		- set negflag to 1
**		- set input to its absolute value
**	3. Fill the result string
**		- digit to char with reval of input modulo base and basestr
**		- after adding divide by the base until input is 0
**		- NULL-term string
**	4. Handle 32 bit signed binary
**		=> ft_bin_32bit_str
**	5. Handle the negflag if it was set to 1
*/

static void	input_normal(long input, char *basestr, char **res)
{
	size_t	i;
	size_t	base;
	int		negflag;

	i = 0;
	base = ft_get_base_from_str(basestr);
	negflag = 0;
	if (input < 0)
	{
		negflag = 1;
		input = ft_abs(input);
	}
	while (input > 0)
	{
		(*res)[i++] = reval((input % base), basestr);
		input /= base;
	}
	(*res)[i] = '\0';
	if (ft_strequal(basestr, B_BIN64))
		(*res) = ft_bin_64bit_str(*res, input, negflag, i);
	if (!ft_strequal(basestr, B_BIN64) && negflag)
	{
		(*res)[i++] = '-';
		(*res)[i] = '\0';
	}
}

/*
**	Helper function to handle edge case: 0
*/

static void	input_zero(long input, char *basestr, char **res)
{
	if (input == 0)
	{
		(*res)[0] = '0';
		(*res)[1] = '\0';
		if (ft_strequal(basestr, B_BIN64))
			(*res) = ft_bin_64bit_str(*res, input, 0, 1);
	}
}

/*
**	Helper function to handle edge case: LONG_MIN
*/

static void	input_negmax(long input, char *basestr, char **res)
{
	size_t	i;
	size_t	base;
	t_ul	negmax;

	i = 0;
	base = ft_get_base_from_str(basestr);
	if (input == LONG_MIN && !ft_strequal(basestr, B_BIN64))
	{
		negmax = (unsigned long)input;
		negmax = ft_abs(negmax);
		while (negmax > 0)
		{
			(*res)[i++] = reval((negmax % base), basestr);
			negmax /= base;
		}
		(*res)[i++] = '-';
		(*res)[i] = '\0';
	}
}

/*
**	MAIN FUNCTION: Converts input to a base defined by basestr into res
**	1. Basic error handling: No res string or No basestr
**	2. Handle input = 0
**		=> input_zero
**	3. Handle input = INT32_MIN
**		IF: signed 32 bit => ft_bin_32bit_str
**		ELSE: => input_negmax
**	4. Handle normal input
**		=> input_normal
**	5. ONLY reverse index order with ft_str_rev
**		WHEN not converting to signed 32 bits
**	RETURN: res filled
*/

char	*ft_long_to_base(char *res, char *basestr, long input)
{
	if (!res || !basestr)
		return (NULL);
	if (input == 0)
		input_zero(input, basestr, &res);
	else if (input == LONG_MIN)
	{
		if (ft_strequal(basestr, B_BIN64))
			ft_bin_64bit_str(res, input, 0, 0);
		else
			input_negmax(input, basestr, &res);
	}
	else
		input_normal(input, basestr, &res);
	if (!ft_strequal(basestr, B_BIN64))
		ft_str_rev(res);
	return (res);
}
