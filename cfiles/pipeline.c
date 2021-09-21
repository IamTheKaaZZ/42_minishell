/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:07:41 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/21 12:05:50 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

static char	*get_full_param(t_list *list_item)
{
	char	*prefix;
	char	*full_param;

	prefix = ft_strjoin_char(list_item->keyword, '=');
	full_param = ft_strjoin(prefix, list_item->content);
	ft_strdel(&prefix);
	return (full_param);
}

char	**get_current_envp(t_list *head)
{
	char	**curr_envp;
	int		n_param;
	int		i;
	t_list	*temp;

	n_param = ft_lstsize(g_mini.env) + 1;
	curr_envp = (char **)ft_calloc(n_param, sizeof(char *));
	if (!curr_envp)
		return (NULL);
	i = -1;
	temp = head;
	while (++i < n_param)
	{
		curr_envp[i] = get_full_param(temp);
		if (!curr_envp[i])
			ft_str_array_del(&curr_envp);
		temp = temp->next;
	}
	return (curr_envp);
}

/*
 * Check if the executable is found AND/OR has execute permissions
*/

static int	is_found_and_or_exec(t_file *f)
{
	if (stat(f->file_path, &f->file_stat) != -1)
	{
		if (f->file_stat.st_mode & S_IXUSR)
			return (2);
		else
		{
			ft_strdel(f->file_path);
			return (1);
		}
	}
	return (0);
}

static char	*get_file_path(char *path, char	*filename)
{
	char	*updated_path;
	char	*file_path;

	updated_path = ft_strjoin_char(path, '/');
	if (!updated_path)
		return (NULL);
	file_path = ft_strjoin(updated_path, filename);
	if (!file_path)
		return (NULL);
	ft_strdel(&updated_path);
	return (file_path);
}

/*
 * Goes through the entire PATH variable until it finds the right path
	-	If it finds it, it checks if the file is executable
	-	> If not executable => throw error
	-	> If it goes through the entire PATH without finding it
			=> throw error
	-	ELSE: return the full path to the executable
*/

char	*get_full_cmd_path(char *command)
{
	t_file	cmd;
	int		i;
	int		check;

	g_mini.path_var = ft_get_path();
	i = -1;
	while (g_mini.path_var[++i])
	{
		cmd.file_path = get_file_path(g_mini.path_var[i], command);
		check = is_found_and_or_exec(&cmd);
		if (check == 2)
			return (cmd.file_path);
		else if (check == 1)
		{
			ft_error_handler(command, errno);
			break ;
		}
		ft_strdel(&cmd.file_path);
	}
	if (g_mini.path_var[i] == NULL)
		ft_error_handler(command, errno);
	ft_strdel(&cmd.file_path);
	return (NULL);
}
