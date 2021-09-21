/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:19:07 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/21 15:20:25 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

/**
 * 	AS IF ARGV = command, flags/arguments, etc, |<>
*/

void	executor(char **argv)
{
	int		i;
	t_file	in;
	t_file	out;

	i = -1;
	while (argv[++i])
	{
		if ((ft_strequal(argv[i], "<") || ft_strequal(argv[i], "<<")
				|| ft_strequal(argv[i], ">") || ft_strequal(argv[i], ">>"))
			&& argv[i + 1] == NULL)
		{
			ft_error_handler("parse error near `\\n\'");
			break ;
		}
		if (ft_strequal(argv[i], "<"))
		{
			if (stat(argv[++i], &in.stats) != -1
				&& in.stats.st_mode & S_IRUSR)
			{
				in.fd = open(argv[i], O_RDONLY);
				if (in.fd == -1)
					ft_error_handler("open");
			}
		}
	}
}
