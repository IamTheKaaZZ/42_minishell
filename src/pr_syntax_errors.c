/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_syntax_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:07:45 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/20 16:36:30 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

static char	*concat_err(char *err, int flag, char *to_add)
{
	static char	syntax[100] = "syntax error near `";
	static char	unspecified[100] = "unspecified special character `";

	if (flag == SYNTAX)
		ft_strlcpy(err, syntax, ft_strlen(syntax) + 1);
	else if (flag == UNSPEC)
		ft_strlcpy(err, unspecified, ft_strlen(unspecified) + 1);
	ft_strlcat(err, to_add, ft_strlen(to_add) + ft_strlen(err) + 1);
	ft_strlcat(err, "'", 2 + ft_strlen(err));
	return (err);
}

static bool	check_special(char **argv, char *err, int i)
{
	int			k;
	static char	sp_chars[20][5] = {"<", "<<", ">", ">>", "|", "&", "\\", "#",
		"=", "[", "]", "!", "{", "}", "(", ")", "*", ";"};

	k = -1;
	while (++k < 6)
		if (ft_strequal(argv[i + 1], sp_chars[k]) && argv[i + 2] == NULL)
			return (err_handler(concat_err(err, 1, sp_chars[k])));
	return (true);
}

bool	syntax_error_check(char **argv, char *err, int i)
{
	int			j;
	static char	sp_chars[20][5] = {"<", "<<", ">", ">>", "|", "&", "\\", "#",
		"=", "[", "]", "!", "{", "}", "(", ")", "*", ";"};

	j = -1;
	while (++j < 18)
	{
		if (j < 6)
		{
			if (ft_strequal(argv[i], sp_chars[j]))
			{
				if (argv[i + 1] == NULL)
					return (err_handler(concat_err(err, 1, "newline")));
			}
			if (!check_special(argv, err, i))
				return (false);
		}
		else
			if (ft_strequal(argv[i], sp_chars[j]))
				return (err_handler(concat_err(err, UNSPEC, sp_chars[j])));
	}
	return (true);
}
