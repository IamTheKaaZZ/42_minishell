#include "../extras/hfiles/minishell.h"

/*
 * Clear all data from the struct
	1.	Clear the env list
	2.	Clear the path ** if it's != NULL && B is specified
	3.	Clear the argv ** if it's != NULL && A OR B is specified
	4.	Free && NULL the prompt string since it has allocated memory from init
*/

int	ft_clear_data(t_minishell *mini, char c)
{
	int	i;

	ft_lstclear(&mini->env, free);
	i = -1;
	if (mini->path && c | B)
	{
		ft_str_array_del(&g_mini.path);
		// while (mini->path[++i])
		// 	ft_strdel(&mini->path[i]);
		// free(mini->path);
	}
	i = -1;
	if (mini->argv && (c | A || c | B))
	{
		ft_str_array_del(&g_mini.argv);
		// while (mini->argv[++i])
		// 	ft_strdel(&mini->argv[i]);
		// free(mini->argv);
	}
	ft_strdel(&mini->prompt);
	rl_clear_history();
	return (0);
}

/*
 * Error codes still need to be figured out
*/

void	ft_error_exit(t_minishell *mini, const char *errmessage)
{
	ft_clear_data(mini, B);
	perror(errmessage);
	exit(EXIT_FAILURE);
}

/*
 * Print the corresponding error message to errno AND update exit_code
    1 - Catchall for general errors
    2 - Misuse of shell builtins (according to Bash documentation)
		-> wrong options/ arguments
    126 - Command invoked cannot execute (Is found but cannot execute)
    127 - “command not found” AKA file/dir/cmd doesn't exist
    128 - Invalid argument to exit
    128+n - Fatal error signal “n”
    130 - Script terminated by Control-C
    255\* - Exit status out of range
*/

int	ft_error_handler(const char *errmessage, int err_code)
{
	if(errno == ENOENT)
		//check for the error and update exit-code accordingly
	perror(errmessage);
	return (err_code);
}

/*
 * Clean the input argv after use
*/

void	ft_clean_input_argv(void)
{
	ft_str_array_del(&g_mini.argv);
}
