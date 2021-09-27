/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:53:50 by bcosters          #+#    #+#             */
/*   Updated: 2021/05/25 15:03:15 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**	Deletes the current list elem and all following ones
**	Then sets the **lst = NULL
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst)
		return ;
	temp = *lst;
	while (*lst != NULL)
	{
		ft_lstdelone(temp, del);
		*lst = (*lst)->next;
		temp = *lst;
	}
	lst = NULL;
}
