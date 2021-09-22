/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:19:07 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/22 12:51:45 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

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

static bool	syntax_error_check(char **argv, char *err, int i)
{
	int			j;
	int			k;
	static char	sp_chars[20][5] = {"<", "<<", ">", ">>", "|", "&", "\\", "#",
		"=", "[", "]", "!", "{", "}", "(", ")", "*", "~", ";"};

	j = -1;
	while (++j < 19)
	{
		if (j < 6)
		{
			if (ft_strequal(argv[i], sp_chars[j]))
			{
				if (argv[i + 1] == NULL)
					return (err_handler(concat_err(err, 1, "newline")));
				k = -1;
				while (++k < 6)
					if (ft_strequal(argv[i + 1], sp_chars[k]))
						return (err_handler(concat_err(err, 1, sp_chars[k])));
			}
		}
		else
			if (ft_strequal(argv[i], sp_chars[j]))
				return (err_handler(concat_err(err, UNSPEC, sp_chars[j])));
	}
	return (true);
}

static void	init_exec(t_exec *ex)
{
	ft_memset(ex, 0, sizeof(t_exec));
	ex->pipe[READ_END] = -1;
	ex->pipe[WRITE_END] = -1;
	ex->prev_fd = -1;
	ex->in.fd = -1;
	ex->out.fd = -1;
}

/**
 * 	AS IF ARGV = command, flags/arguments, etc, |<>
 * ->	| as argv[0] is a syntax error
 * ->	<< EOF with "<<" as argv[0] still works without command
 * 	BUT: DOESN'T DO ANYTHING -> << EOF >> file creates empty file
 *  	-> STILL OPENS AN INPUTSTREAM BEFORE DOING NOTHING
 * -> "> file": creates an empty file
 * -> "< file": opens and closes the file succesfully (exit_code 0)
*/

int	executor(char **argv)
{
	int			i;
	t_exec		ex;

	init_exec(&ex);
	i = -1;
	while (argv[++i])
	{
		if (ft_strequal(argv[0], "|"))
			return (err_handler(concat_err(ex.err, SYNTAX, "|")));
		if (!syntax_error_check(argv, ex.err, i))
			break ;
		if (ft_strequal(argv[i], "<"))
		{
			if (stat(argv[++i], &ex.in.stats) != -1
				&& ex.in.stats.st_mode & S_IRUSR)
			{
				ex.in.fd = open(argv[i], O_RDONLY);
				if (ex.in.fd == -1)
					return (err_handler("open"));
			}
			else
				return (err_handler(argv[i]));
		}
	}
	return (EXIT_SUCCESS);
}
