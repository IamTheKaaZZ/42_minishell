/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:49:27 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/27 15:23:36 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

/**
 * Modified lst_new for the project
 * -> param = ft_split by '=' on the parameter
 * -> param needs to be free'd either in here or in the fucntion calling this
*/

t_env	*new_env_param(char **param)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->keyword = param[0];
	new->content = param[1];
	new->next = NULL;
	return (new);
}

static t_env	*find_tail(t_env *head)
{
	t_env	*temp;

	temp = head;
	while (temp != NULL)
	{
		if (temp->next == NULL)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

/**
 * Modified lst_add_back to fit the project
*/

void	add_to_tail(t_env **env, t_env *new)
{
	if (!*env)
	{
		new->next = *env;
		*env = new;
	}
	else
		find_tail(*env)->next = new;
}

/**
 * Find any param in the env list
*/

t_env	*find_param(t_env **env, char *keyword)
{
	t_env	*temp;

	temp = *env;
	if (temp != NULL && ft_strequal(temp->keyword, keyword))
		return (temp);
	while (temp != NULL && !ft_strequal(temp->keyword, keyword))
		temp = temp->next;
	if (temp == NULL)
		return (NULL);
	else
		return (temp);
}

/**
 * Count the amount of parameters in the list
*/

int	count_params(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}
