/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lt_get_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:14:37 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/29 17:17:46 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/*
 * Check if the executable is found AND/OR has execute permissions
*/

static int	is_found_and_or_exec(t_file *f)
{
	if (stat(f->file_path, &f->stats) != -1)
	{
		if (f->stats.st_mode & S_IXUSR)
			return (2);
		else
		{
			ft_strdel(&f->file_path);
			return (1);
		}
	}
	return (0);
}

/**
 * Check if the executable has it's full path for execve
 * -> IF: It already has '/' in the filename, it already has the path
 * -> ELSE: Add a '/' to the path, then join it with the filename
 * -> RETURN: The full path to the filename
*/

static char	*get_file_path(char *path, char	*filename)
{
	char	*updated_path;
	char	*file_path;

	if (ft_ischrinset(filename, '/'))
		return (ft_strdup(filename));
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
	-	@get_file_path checks if the command given already has a full path
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
			g_mini.exit_code = 126;
			err_handler(command);
			break ;
		}
		ft_strdel(&cmd.file_path);
	}
	if (g_mini.path_var[i] == NULL)
		err_handler(command);
	ft_strdel(&cmd.file_path);
	return (NULL);
}

/*
 * If the path was already set, reset it
*/

char	**ft_get_path(void)
{
	t_node	*path;

	if (g_mini.path_var)
		ft_str_array_del(&g_mini.path_var);
	path = find_param(&g_mini.env, "PATH");
	return (ft_split(path->content, ':'));
}

/**
 * Create the list of the starting environment variables
*/

void	ft_env_list(char **env)
{
	int		i;
	t_node	*new;
	char	**split_param;

	new = NULL;
	i = -1;
	while (env[++i])
	{
		split_param = ft_split(env[i], '=');
		new = new_env_param(split_param);
		if (!new)
		{
			clear_env_list(&g_mini.env);
			return ;
		}
		add_to_tail(&g_mini.env, new);
	}
}
