/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nice_prompt_bro.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:27:15 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/22 17:45:34 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

static char	*get_full_prefix(void)
{
	static char	prefix[100] = "\033[33m𝓶 𝓲𝓷𝓲𝓼𝓱𝓮𝓵𝓵 \033[37;1m➫ ＠〈 ";
	char		cwd[100];
	static char	closebracket[100] = " 〉➫ \033[0m";
	char		*home;
	char		path[100];

	ft_bzero(cwd, 100);
	ft_bzero(path, 100);
	getcwd(cwd, 100);
	home = find_param(&g_mini.env, "HOME")->content;
	if (ft_strncmp(home, cwd, ft_strlen(home)) == 0)
	{
		ft_strlcpy(path, "~/", 2);
		ft_strlcat(path, cwd + ft_strlen(home), 100);
		ft_strlcat(prefix, path, 100);
		ft_strlcat(prefix, closebracket, 100);
		return (prefix);
	}
	ft_strlcat(prefix, cwd, 100);
	ft_strlcat(prefix, closebracket, 100);
	return (prefix);
}

void	pretty_prompt(void)
{
	char		*prefix;
	static char	good[100] = "\033[0;32;1m⸢+𝟜𝟚⸥\033[37;1m ➫ \033[0m";
	static char	bad[100] = "\033[0;31;1m⸢-𝟜𝟚⸥\033[37;1m ➫ \033[0m";

	prefix = get_full_prefix();
	if (g_mini.prompt)
		ft_strdel(&g_mini.prompt);
	if (g_mini.exit_code == 0)
		g_mini.prompt = ft_strjoin(prefix, good);
	else
		g_mini.prompt = ft_strjoin(prefix, bad);
	if (!g_mini.prompt)
		ft_error_exit("malloc");
}

void	intro_message(void)
{
	static char	intro[200] = "The default shell is now ";

	ft_strlcat(intro, "\033[33m𝓶 𝓲𝓷𝓲𝓼𝓱𝓮𝓵𝓵\033[0m\n", 200);
	ft_strlcat(intro, "Powered by the brain cells of ", 200);
	ft_strlcat(intro, "\033[35m@bcosters\033[0m ", 200);
	ft_strlcat(intro, "and \033[35m@fbarros\033[0m.\n", 200);
	ft_strlcat(intro, "For more details, please RTFM.\n\n", 200);
	ft_putstr(intro);
}
