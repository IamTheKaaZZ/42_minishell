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

void	ft_echo(void)
/*	Rought-cut

	expanding variables ??
		var search function
	*/
{
	if (ft_strequal(g_mini.argv[1], "-n"))
		ft_putendl_fd(g_mini.input + 5, 1);
	else
		ft_putnstr_fd(g_mini.input + 8, ft_strlen(g_mini.input) - 8, 1);
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
	if (g_mini.argv[1] && !ft_strchr("<>|&", *g_mini.argv[1]))
	{
		err_handler("pwd: too many arguments");
	}
	else
	{
		buf = getcwd(NULL, 0);
		if (!buf)
			err_handler("Failed to get current working directory.");
		ft_putendl_fd(buf, 1);
		free(buf);
	}
}

void	ft_env(void)
/* t_env functions (-> env_list.c):
	
	t_env *
-	new_env_param(char **param)

	static t_env *
-	find_tail(t_env *head)
	
	void
-	add_to_tail(t_env **env, t_env *new)

	t_env *
-	find_param(t_env **env, char *keyword)

	int
-	count_params(t_env *env)
*/
{
	t_env	*head;

	head = g_mini.env;
	while (head->next)
	{
		ft_putstr_fd(head->keyword, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(head->content, 1);
		head = head->next;
	}
}

