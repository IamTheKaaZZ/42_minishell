/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_syntax_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:07:45 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/28 11:28:33 by bcosters         ###   ########.fr       */
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
			return (err_handler(concat_err(err, 1, sp_chars[k]), 1, 0));
	return (true);
}

bool	syntax_error_check(char **argv, char *err, int i)
{
	int			j;
	static char	sp[20][5] = {"<", "<<", ">", ">>", "|", "&", "\\", "#",
		"=", "[", "]", "!", "{", "}", "(", ")", "*", ";"};

	j = -1;
	while (++j < 18)
	{
		if (j < 6)
		{
			if (ft_strequal(argv[i], sp[j]))
			{
				if (argv[i + 1] == NULL)
					return (err_handler(concat_err(err, 1, "newline"), 1, 0));
			}
			if (!check_special(argv, err, i))
				return (false);
		}
		else
			if (ft_strequal(argv[i], sp[j]))
				return (err_handler(concat_err(err, UNSPEC, sp[j]), 1, 0));
	}
	return (true);
}

bool	check_export_syntax(char *arg)
{
	static char	suffix[100] = "': not a valid identifier";
	char		error[300];

	ft_bzero(error, 300);
	ft_strlcpy(error, "`", 2);
	if (str_contains_chars(arg, " ") || arg[0] == '=' || ft_isdigit(arg[0]))
	{
		ft_strlcat(error, arg, 300);
		ft_strlcat(error, suffix, 300);
		return (err_handler(error, 2, false));
	}
	return (true);
}
