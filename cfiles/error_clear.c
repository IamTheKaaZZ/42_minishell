#include "../extras/hfiles/minishell.h"

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

	ft_lstclear(&g_mini.env, free);
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
    127 - “command not found” AKA file/dir/cmd doesn't exist
    128 - Invalid argument to exit
    128+n - Fatal error signal “n”
    130 - Script terminated by Control-C
    255\* - Exit status out of range
*/

int	ft_error_handler(const char *errmessage)
{
	if (errno == ENOENT || errno == ENOTDIR || errno == EBADF
		|| errno == EACCES || errno == EFAULT)
		g_mini.exit_code = 127;
	else if (g_mini.exit_code == 0)
		g_mini.exit_code = 1;
	write(2, "minishell: ", 12);
	perror(errmessage);
	return (false);
}

/*
 * Clean the input argv after use
*/

void	ft_clean_input_argv(void)
{
	ft_str_array_del(&g_mini.argv);
}
