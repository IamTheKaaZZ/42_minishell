/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:27:30 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/29 12:54:44 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/**
 * Remove any parameter from the environment searching by keyword
 * -> Keep track of the previous one to reconnect the list at the end
 * -> If the parameter is not found, do nothing
 * -> IF IT IS FOUND: Connect the previous one and the next one
 * 		->	Delete and free the disconnected parameter
*/

void	remove_param(t_node **env, char	*keyword)
{
	t_node	*temp;
	t_node	*prev;

	temp = *env;
	if (temp != NULL && ft_strequal(temp->keyword, keyword))
	{
		*env = (*env)->next;
		ft_strdel(&temp->keyword);
		ft_strdel(&temp->content);
		free(temp);
		temp = NULL;
		return ;
	}
	while (temp != NULL && !ft_strequal(temp->keyword, keyword))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	ft_strdel(&temp->keyword);
	ft_strdel(&temp->content);
	free(temp);
	temp = NULL;
}

/**
 * Modified lst_clear for the project
*/

void	clear_list(t_node **head, bool clear)
{
	t_node	*temp;

	if (!head)
		return ;
	temp = *head;
	while (*head != NULL)
	{
		if (clear == true)
		{
			ft_strdel(&temp->keyword);
			ft_strdel(&temp->content);
		}
		*head = (*head)->next;
		free(temp);
		temp = NULL;
		temp = *head;
	}
}
/*
 * Clear all data from the struct
	1.	Clear the env list
	2.	Clear the path ** if it's != NULL && B is specified
	3.	Clear the argv ** if it's != NULL && A OR B is specified
	4.	Free && NULL the prompt string since it has allocated memory from init
*/

int	ft_clear_data(void)
{
	int	i;

	clear_list(&g_mini.env, true);
	i = -1;
	if (g_mini.path_var)
		ft_str_array_del(&g_mini.path_var);
	i = -1;
	if (g_mini.argv)
		ft_str_array_del(&g_mini.argv);
	ft_strdel(&g_mini.prompt);
	ft_strdel(&g_mini.cwd);
	rl_clear_history();
	return (EXIT_SUCCESS);
}

/*
 * Error codes still need to be figured out
*/

void	ft_error_exit(const char *errmessage)
{
	ft_clear_data();
	perror(errmessage);
	exit(EXIT_FAILURE);
}

/*
 * Print the corresponding error message to errno AND update exit_code
    1 - Catchall for general errors
    2 - Misuse of shell builtins (according to Bash documentation)
		-> wrong options/ arguments
    126 - Command invoked cannot execute (Is found but cannot execute)
    127 - ???command not found??? AKA file/dir/cmd doesn't exist
    128 - Invalid argument to exit
    128+n - Fatal error signal ???n???
    130 - Script terminated by Control-C
    255\* - Exit status out of range
*/

bool	err_handler(const char *errmessage, t_uc e_code, bool print_errno)
{
	g_mini.exit_code = e_code;
	write(2, "minishell: ", 12);
	if (print_errno)
		perror(errmessage);
	else
		ft_putendl_fd((char *)errmessage, 2);
	return (false);
}
