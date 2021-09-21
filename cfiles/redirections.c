/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:19:07 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/21 16:20:20 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

/**
 * 	AS IF ARGV = command, flags/arguments, etc, |<>
 * ->	<< EOF with "<<" as argv[0] still works without command
 * 	BUT: DOESN'T DO ANYTHING -> << EOF >> file creates empty file
 *  	-> STILL OPENS AN INPUTSTREAM BEFORE DOING NOTHING
*/

void	executor(char **argv)
{
	int		i;
	t_exec	ex;

	i = -1;
	while (argv[++i])
	{
		if ((ft_strequal(argv[i], "<") || ft_strequal(argv[i], "<<")
				|| ft_strequal(argv[i], ">") || ft_strequal(argv[i], ">>"))
			&& argv[i + 1] == NULL)
		{
			ft_error_handler("syntax error near unexpected token `newline'");
			break ;
		}
		if (ft_strequal(argv[i], "<"))
		{
			if (stat(argv[++i], &ex.in.stats) != -1
				&& ex.in.stats.st_mode & S_IRUSR)
			{
				ex.in.fd = open(argv[i], O_RDONLY);
				if (ex.in.fd == -1)
				{
					ft_error_handler("open");
					break ;
				}
			}
			else
			{
				ft_error_handler(argv[i]);
				break ;
			}
		}
	}
}
