/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:14:50 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/17 15:00:09 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/hfiles/minishell.h"

/*
 * All builtins set the exit_code to 2 on failure
*/

void	ft_export(t_minishell *mini) // blad
{
	t_list	*temp;

	temp = mini->env;
	ft_lstadd_back(&temp, ft_lstnew(ft_split(mini->argv[1], '=')));
}

void	ft_unset(t_minishell *mini) // co za kurwa gowno
{
	t_list	*temp;
	t_list	*current;
	int		i;

	temp = mini->env;
	current = mini->env;
	i = 0;
	while (mini->argv[1])
		i++;
	while (temp)
	{
		if (!ft_strncmp(temp->next->keyword, mini->argv[1], i))
		{
			current = current->next;
			temp->next = current->next;
			free(current);
			current = NULL;
			break ;
		}
		temp = temp->next;
		current = current->next;
	}
}

void	ft_env(t_minishell *mini)
{
	t_list	*temp;

	temp = mini->env;
	while (temp)
	{
		printf("%s%s\n", ft_strjoin(temp->keyword, "="), temp->content);
		temp = temp->next;
	}
}

void	ft_exit(t_minishell *mini)
{
	ft_clear_data(mini, B);
	exit(EXIT_SUCCESS);
}

void	ft_cd(t_minishell *mini)
{
	if (chdir(mini->argv[1]) == -1)
	{
		ft_error_handler("Builtin CD", ENOENT);
	}
}

void	ft_pwd(t_minishell *mini)
{
	t_list	*temp;

	temp = mini->env;
	while (temp)
	{
		if (!ft_strncmp(temp->keyword, "PWD", 3))
		{
			ft_putstr_fd(temp->content, 1);
			break;
		}
		temp = temp->next;
	}
}

void	ft_echo(void)
{
	int i;

	i = 0;
	while (g_mini.argv[++i])
	{
		printf("%s", g_mini.argv[i]);
		if (g_mini.argv[i + 1])
			printf(" ");
	}
	printf("\n");
}

void	ft_echon(t_minishell *mini)
{
	int	i;

	i = 1;
	while (mini->argv[++i])
	{
		printf("%s", mini->argv[i]);
		if (mini->argv[i + 1])
			printf(" ");
	}
	printf("%%\n");
}

void	ft_path(void)
{
	int		i;
	int		child_id;
	char	*cmd_path;

	i = -1;
	child_id = fork();
	if (child_id == -1)
		printf("Error FORK\n");
	else if (child_id == 0)
	{
		while (g_mini.path[++i])
		{
			cmd_path = ft_strjoin(g_mini.path[i], g_mini.argv[0]);
			if (execve(strjoin2, &mini->argv[0], NULL))
				;
			ft_strdel(&cmd_path);
		}
	}
	else
		wait(NULL);
}
