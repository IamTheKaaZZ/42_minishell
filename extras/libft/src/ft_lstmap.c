/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:22:59 by bcosters          #+#    #+#             */
/*   Updated: 2021/04/08 16:55:24 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**	1.	Checks if lst or f exist
**	2.	Checks if initial allocation for resultlist fails
**		(Call lstnew with the function applied to the lst content)
**		IF YES: Call listclear to free and delete the contents
**		IF NO:	Continue
**	3.	Set tempresult = resultlist and move lst to the next one
**	4.	Iteratively set the next one to a new list elem with f(lst->content)
**	5.	Whenever allocation fails -> call lstclear to free and del content
**	6.	If no allocation fails then return the resultlist
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*resultlist;
	t_list	*tempres;

	if (!lst || !f)
		return (NULL);
	resultlist = ft_lstnew(f(lst->content));
	if (!(resultlist))
		ft_lstclear(&resultlist, del);
	else
	{
		tempres = resultlist;
		lst = lst->next;
		while (lst != NULL)
		{
			tempres->next = ft_lstnew(f(lst->content));
			if (!(tempres->next))
				ft_lstclear(&tempres, del);
			tempres = tempres->next;
			lst = lst->next;
		}
	}
	return (resultlist);
}
