/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:14:50 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/27 16:38:32 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

/*error handling!!*/

static char	*ft_strupdate(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	if (!s1)
		return (s2);
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	if (!s1)
		return (NULL);
	return(s1);
}

char	*ft_echo(void)
/*	Rought-cut

	expanding variables ??
		var search function
	*/
{
	char	**argp;
	bool	nl;
	char	*buf; // return or save in struct?

	nl = 1;
	argp = g_mini.argv; // if g_mini.argv == "ëcho"
	if (*(++argp) && !ft_strcmp(*argp, "-n"))
		nl = 0;
	while (++argp && *argp)
	{
		if (ft_strchr("|<>", **argp))
			return (buf);
		buf = ft_strupdate(buf, *argp);
	}
	if (!buf)
		return (NULL);
	ft_putstr_fd(buf, 1);
	if (nl)
		write(1, "\n", 1);
	free(buf);
	return (0);
	// if '>'or somthn ??
}

void	ft_cd(void)
/*int
-  chdir(const char *path); returns 0 or -1 (errno)

  int
-  stat(const char *restrict path, struct stat *restrict buf);

  int
-  lstat(const char *restrict path, struct stat *restrict buf);

  int
-  fstat(int fildes, struct stat *buf);

	DIR *
-	opendir(const char *filename);

	struct dirent *
-	readdir(DIR *dirp);

	int
-	closedir(DIR *dirp);

	if starting with '/' just pass string to function
	if starting with '~' look for $HOME 
	else look for repository in current wd*/
{
	DIR				*dir;
	// struct dirent	*s_dir;

	//check argv[1] for validity
	dir = opendir(g_mini.argv[1]);
	if (!dir)
	{
		err_handler("Failed to open directory.");
		return ;
	}

	// if (chdir(g_mini.input + 2) == -1)
	// 	err_handler("Function chdir returned an error.");

	if (closedir(dir))
		err_handler("Failed to close directory.");
}

void	ft_pwd(void)
/*char *
  getcwd(char *buf, size_t size);
*/
{
	char	*buf;

	buf = NULL;
	if (g_mini.argv[1] && !ft_strchr("<>|", *g_mini.argv[1])) // ??
	{
		err_handler("pwd: too many arguments");
	}
	else
	{
		buf = getcwd(NULL, 0);
		if (!buf)
		{
			free(buf);
			err_handler("Failed to get current working directory.");
		}
		ft_putendl_fd(buf, 1);
		free(buf);
	}
}

void	ft_env(void)
/* t_node functions (-> env_list.c):
	
	t_node *
-	new_env_param(char **param)

	static t_node *
-	find_tail(t_node *head)

	void
-	add_to_tail(t_node **env, t_node *new)

	t_node *
-	find_param(t_node **env, char *keyword)

	int
-	count_params(t_node *env)
*/
{
	t_node	*head;

	head = g_mini.env;
	while (head->next)
	{
		ft_putstr_fd(head->keyword, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(head->content, 1);
		head = head->next;
	}
}

