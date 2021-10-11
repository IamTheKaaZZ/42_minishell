/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_special_split_chars.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:03:01 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/11 13:25:16 by bcosters         ###   ########.fr       */
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
	while (**p->str && **p->str == c)
		(*p->str)++;
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

static void	strlen_redirect(t_parse *p, char arrow)
{
	p->start = strchr_index(*p->str, arrow);
	if (p->start > 0)
		*p->len = p->start;
	else if ((*p->str)[p->start + 1] != 0 && (*p->str)[p->start + 1] == arrow)
		*p->len = 2;
	else
		*p->len = 1;
}

void	split_redirections(t_parse *p)
{
	if (char_before_others(*p->str, '|', "<>"))
	{
		p->start = strchr_index(*p->str, '|');
		if (p->start > 0)
			*p->len = p->start;
		else
			*p->len = 1;
	}
	else if (char_before_others(*p->str, '<', ">"))
		strlen_redirect(p, '<');
	else if (char_before_others(*p->str, '>', "<"))
		strlen_redirect(p, '>');
	p->bools->no_quote = true;
}
