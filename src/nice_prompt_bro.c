/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nice_prompt_bro.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:27:15 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/29 11:22:35 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

static void	check_env(t_prompt *p)
{
	ft_bzero(p, sizeof(t_prompt));
	if (!find_param("PWD"))
		p->cwd = getcwd(NULL, 0);
	else
		p->cwd = find_param("PWD")->content;
	if (find_param("HOME"))
		p->home = find_param("HOME")->content;
	else
		p->home = ft_strdup(getenv("HOME"));
}

static char	*get_full_prefix(void)
{
	static char	prefix[100] = "\033[33mð¶ ð²ð·ð²ð¼ð±ð®ðµðµ \033[37;1mâ« ï¼ ã ";
	static char	closebracket[100] = " ãâ« \033[0m";
	t_prompt	p;

	check_env(&p);
	if (*p.home && (ft_strncmp(p.home, p.cwd, ft_strlen(p.home)) == 0))
	{
		p.path = ft_strjoin("~", p.cwd + ft_strlen(p.home));
		p.full = p.path;
		p.path = ft_strjoin(p.full, closebracket);
		ft_strdel(&p.full);
		p.full = ft_strjoin(prefix, p.path);
		ft_strdel(&p.path);
		return (p.full);
	}
	p.path = ft_strjoin(prefix, p.cwd);
	p.full = ft_strjoin(p.path, closebracket);
	ft_strdel(&p.path);
	if (!find_param("PWD"))
		ft_strdel(&p.cwd);
	if (!find_param("HOME"))
		ft_strdel(&p.home);
	return (p.full);
}

void	pretty_prompt(void)
{
	char		*prefix;
	static char	good[100] = "\033[0;32;1mâ¸¢+ððâ¸¥\033[37;1m â« \033[0m";
	static char	bad[100] = "\033[0;31;1mâ¸¢-ððâ¸¥\033[37;1m â« \033[0m";

	prefix = get_full_prefix();
	if (g_mini.prompt)
		ft_strdel(&g_mini.prompt);
	if (g_mini.exit_code == 0)
		g_mini.prompt = ft_strjoin(prefix, good);
	else
		g_mini.prompt = ft_strjoin(prefix, bad);
	if (!g_mini.prompt)
		ft_error_exit("malloc");
	ft_strdel(&prefix);
}

void	intro_message(char *execpath)
{
	static char	intro[200] = "The default shell is now ";
	int			shlvl;

	ft_strlcat(intro, "\033[33mð¶ ð²ð·ð²ð¼ð±ð®ðµðµ\033[0m\n", 200);
	ft_strlcat(intro, "Powered by the brain cells of ", 200);
	ft_strlcat(intro, "\033[35m@bcosters\033[0m ", 200);
	ft_strlcat(intro, "and \033[35m@fbarros\033[0m.\n", 200);
	ft_strlcat(intro, "For more details, please RTFM.\n\n", 200);
	shlvl = ft_atoi(find_param("SHLVL")->content);
	shlvl++;
	ft_strdel(&find_param("SHLVL")->content);
	find_param("SHLVL")->content = ft_itoa(shlvl);
	ft_strdel(&find_param("SHELL")->content);
	find_param("SHELL")->content = ft_strdup(execpath);
	ft_putstr(intro);
}
