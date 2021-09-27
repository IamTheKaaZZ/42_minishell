/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:17:06 by bcosters          #+#    #+#             */
/*   Updated: 2021/03/30 11:36:35 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Main function sorts a tab of ints in ascending order
*/

static void	ft_swap(int *a, int *b)
{
	int	swap;

	swap = *b;
	*b = *a;
	*a = swap;
}

void	ft_sort_int_tab(int *tab, int size)
{
	int	index1;
	int	index2;
	int	*ptr_a;
	int	*ptr_b;

	index1 = 0;
	while (index1 < size)
	{
		index2 = 0;
		while (index2 < size)
		{
			if (tab[index2] > tab[index2 + 1])
			{
				ptr_a = &tab[index2];
				ptr_b = &tab[index2 + 1];
				ft_swap(ptr_a, ptr_b);
			}
			index2++;
		}
		index1++;
	}
}
