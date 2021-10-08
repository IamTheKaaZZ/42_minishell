/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:14:50 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/07 11:05:51 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

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
error handling!!*/

void	ft_echo(void)
/*	Rought-cut

	expanding variables ??
		var search function
	*/
{
	int		i;
	bool	nl;

	nl = 1;
	i = 1;
	if (g_mini.argv[i])
	{
		if (!ft_strcmp(g_mini.argv[i], "-n"))
		{
			nl = 0;
			i++;
		}
		while (g_mini.argv[i])
		{
			if ((nl && i > 1) || (!nl && i > 2)) // terrible
				ft_putchar_fd(' ', 1);
			if (str_contains_chars(g_mini.argv[i], "|<>&"))
				return ; // for now
			ft_putstr_fd(g_mini.argv[i++], 1);
		}
	}
	if (nl)
		write(1, "\n", 1);
}

void	ft_cd(void)
/** WAITING FOR ~ TO BE DEALT WITH
 * if starting with '~' look for $HOME 
	change $PWD*/
{
	char	err[100];
	char	*path; // if tilde
	char	**env_var;

	env_var = NULL;
	path = g_mini.argv[1];
	if (!path)
		return ;
	ft_bzero(err, 100);
	/*PROTO*/
	if (*path == '~')
	{
		if (chdir(find_param(&g_mini.env, "HOME")->content))
		{
			err_handler("chdir find_param err!!!!!!!!");
			return ;
		}
		path++;
	}
	/*PROTO*/
	if (path && chdir(path) == -1)
	{
		ft_strlcat(err, "cd: ", 5);
		ft_strlcat(err, g_mini.argv[1], ft_strlen(g_mini.argv[1]));
		err_handler(err);
		return ;
	}
	path = getcwd(NULL, 0);
	env_var = &find_param(&g_mini.env, "PWD")->content;
	if (!path || !env_var)
	{
		ft_strlcat(err, "cd: ", 5);
		ft_strlcat(err, g_mini.argv[1], ft_strlen(g_mini.argv[1]));
		err_handler(err);
		return ;
	}
	free(*env_var);
	*env_var = path;
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

