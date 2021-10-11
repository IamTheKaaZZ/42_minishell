/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_special_split_chars.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:03:01 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/11 11:18:04 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/*
**	Iteratively finds the next string and corresponding lenght*
**	Every time this gets called.
*/

void	get_next_str_len(t_parse *p, char c)
{
	size_t	i;

	*p->len = 0;
	i = 0;
	if (skip == true)
	{
		while (**p->str && **p->str == c)
			(*p->str)++;
	}
	while ((*p->str)[i])
	{
		if ((*p->str)[i] == c)
		{
			p->bools->no_quote = true;
			return ;
		}
		(*p->len)++;
		i++;
	}
	p->bools->no_quote = true;
}
