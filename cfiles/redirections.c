/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:19:07 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/22 11:30:45 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

static char	*concat_err(int flag, char *to_add)
{
	static char	syntax[100] = "syntax error near `";
	static char	unspecified[100] = "unspecified special character `";
	char		base[100];

	if (flag == SYNTAX)
		ft_strlcpy(base, syntax, ft_strlen(syntax) + 1);
	else if (flag == UNSPEC)
		ft_strlcpy(base, unspecified, ft_strlen(unspecified) + 1);
	ft_strlcat(base, to_add, ft_strlen(to_add) + 1);
	ft_strlcat(base, "'", 2);
	return (base);
}

static bool	syntax_error_check(char **argv, char **sp_chars, int i)
{
	int			j;
	int			k;

	j = -1;
	while (sp_chars[++j])
	{
		if (j < 6)
		{
			if (ft_strequal(argv[i], sp_chars[j]))
			{
				if (argv[i + 1] == NULL)
					return (ft_error_handler(concat_err(SYNTAX, "newline")));
				k = 6;
				while (--k)
					if (ft_strequal(argv[i + 1], sp_chars[k]))
						return (ft_error_handler(concat_err(SYNTAX,
									sp_chars[k])));
			}
		}
		else
			if (ft_strequal(argv[i], sp_chars[j]))
				return (ft_error_handler(concat_err(UNSPEC, sp_chars[j])));
	}
	return (true);
}

/**
 * 	AS IF ARGV = command, flags/arguments, etc, |<>
 * ->	<< EOF with "<<" as argv[0] still works without command
 * 	BUT: DOESN'T DO ANYTHING -> << EOF >> file creates empty file
 *  	-> STILL OPENS AN INPUTSTREAM BEFORE DOING NOTHING
*/

void	executor(char **argv)
{
	int			i;
	t_exec		ex;
	static char	special_chars[20][5] = {
		"<", "<<", ">", ">>", "|", "&", "\\", "#", "=", "[", "]", "!", "{", "}",
			"(", ")", "*", "~", ";", NULL
	};

	i = -1;
	while (argv[++i])
	{
		if (syntax_error_check(argv, special_chars, i))
			break ;
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
