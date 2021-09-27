/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:24:35 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:51:23 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_bonus.h"

static void	addchar_to_str(char **str, char c)
{
	char	*temp;

	temp = *str;
	*str = ft_strjoin_char(temp, c);
	if (temp)
		ft_strdel(&temp);
}

static void	handle_prec_out_range(char **ftoastr, double *fpart, int *prec)
{
	if (*fpart < 0)
		*fpart = -(*fpart);
	addchar_to_str(ftoastr, '.');
	*fpart = ft_bankers_round(*fpart, *prec);
	if (*prec > 6 && (*fpart) == ft_bankers_round(*fpart, *prec))
	{
		while (*fpart != 0 && (*prec)--)
		{
			*fpart *= 10;
			if (*prec == 0)
				*fpart += 1;
			addchar_to_str(ftoastr, ((int)(*fpart) + '0'));
			*fpart -= (int)(*fpart);
		}
	}
	else
	{
		while (*fpart != 0 && (*prec)--)
		{
			*fpart *= 10;
			addchar_to_str(ftoastr, ((int)(*fpart) + '0'));
			*fpart -= (int)(*fpart);
		}
	}
}

static char	*easy_rounding(char *fractstr, int *prec)
{
	int	i;

	i = 0;
	while (*prec - i > 0)
	{
		if (*(fractstr + *prec - i) >= '5')
		{
			if (*(fractstr + *prec - i) != '9'
				&& *(fractstr + *prec - i + 1) >= '5'
				&& *(fractstr + *prec - i + 2) >= '5')
			{
				fractstr[*prec]++;
				break ;
			}
			if (*(fractstr + *prec) == '9')
			{
				fractstr[*prec] = '0';
				fractstr[*prec - i] = '1';
				break ;
			}
		}
		i++;
	}
	fractstr[*prec + 1] = '\0';
	return (fractstr);
}

static void	handle_prec_within_range(char **ftoastr, double *fpart, int *prec)
{
	char	*fractstr;
	char	*temp;
	double	power;

	power = ft_iterative_power(10, *prec + 2);
	fractstr = NULL;
	if (*fpart < 0)
		*fpart = -(*fpart);
	addchar_to_str(ftoastr, '.');
	*fpart += 1.0;
	*fpart *= power;
	*fpart = ft_roundf(*fpart, *prec);
	fractstr = ft_ultoa_base((t_ull)(*fpart), B_DEFAULT);
	fractstr = easy_rounding(fractstr, prec);
	temp = *ftoastr;
	*ftoastr = ft_strjoin(temp, fractstr + 1);
	if (temp)
		ft_strdel(&temp);
	ft_strdel(&fractstr);
}

char	*ft_ftoa(double nb, int prec)
{
	double	ipart;
	double	fpart;
	char	*ftoastr;

	ipart = 0;
	fpart = ft_modf(nb, &ipart);
	if (ft_almost_eq_rel(nb, 0, __FLT_EPSILON__))
		ftoastr = ft_ultoa_base(0, B_DEFAULT);
	else
	{
		if (prec == 0 && fpart >= 0.5)
			ipart += 1;
		else if (fpart >= 0.9)
			fpart = ft_modf(ft_roundf(nb, prec), &ipart);
		ftoastr = ft_ltoa_base((t_ll)ipart, B_DEFAULT);
	}
	if (prec != 0 && prec <= 6)
		handle_prec_within_range(&ftoastr, &fpart, &prec);
	else if (prec != 0)
		handle_prec_out_range(&ftoastr, &fpart, &prec);
	while (fpart == 0 && prec--)
		addchar_to_str(&ftoastr, '0');
	return (ftoastr);
}
