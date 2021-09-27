/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:25:18 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:54:06 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**	If the list is empty, add to the front
**	else, next of the last one = new
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!*lst)
		ft_lstadd_front(lst, new);
	else
		ft_lstlast(*lst)->next = new;
}
