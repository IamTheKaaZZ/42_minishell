# Minishell (42 Project)
> <span style="color:green">***Final score 101/100***</span>
## As beautiful as a shell
Summary:
- The objective of this project is for you to create a simple shell.
- Yes, your little bash or zsh.
- You will learn a lot about processes and file descriptors.

## Introduction
The existence of shells is linked to the very existence of IT.<br> At the time, all coders agreed that communicating with a computer using aligned 1/0 switches was seriously irritating.<br> It was only logical that they came up with the ideato communicate witha computer using interactive lines of commands in a language somewhat close to english.<br>With Minishell, you’ll be able to travel through time and come back to problems people faced when Windows didn’t exist.

## Description

| Program name     | minishell                                                                                                                                                                                                                                                                                                                                                                                                                                            |
|------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| External functs. | readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs |
| Libft authorized | Yes                                                                                                                                                                                                                                                                                                                                                                                                                                                  |
| Description      | Write a shell                                                                                                                                                                                                                                                                                                                                                                                                                                        |

Your shell should:
<br>• Not interpret unclosed quotes or unspecified special characters like\or;.
<br>• Not use more than one global variable, think about it and be ready to explain why you do it.
<br>• Show a prompt when waiting for a new command.
<br>• Have a working History.
<br>• Search and launch the right executable (based on the PATH variable or by using relative or absolute path)
<br>• It must implement the builtins:
<br>&emsp;◦ echo with option -n
<br>&emsp;◦ cd with only a relative or absolute path
<br>&emsp;◦ pwd with no options
<br>&emsp;◦ export with no options
<br>&emsp;◦ unset with no options
<br>&emsp;◦ env with no options or arguments
<br>&emsp;◦ exit with no options
<br>• `’` inhibit all interpretation of a sequence of characters.
<br>• `"` inhibit all interpretation of a sequence of characters except for `$`.
<br>• Redirections:
<br>&emsp;◦ `<` should redirect input.
<br>&emsp;◦ `>` should redirect output.
<br>&emsp;◦ `<<` read input from the current source until a line containing only the de-limiter is seen. it doesn’t need to update history!
<br>&emsp;◦ `>>` should redirect output with append mode.
<br>• Pipes `|`: The output of each command in the pipeline is connected via a pipe to theinput of the next command.
<br>• Environment variables (`$followed by characters`) should expand to their values.
<br>• `$?` should expand to the exit status of the most recently executed foreground pipeline.
<br>• `ctrl-C ctrl-D ctrl-\` should work like in bash.
<br>• When interactive:
<br>&emsp;◦ `ctrl-C`: print a new prompt on a newline.
<br>&emsp;◦ `ctrl-D`; exit the shell.
<br>&emsp;◦ `ctrl-\`: do nothing.
<br>EXTRA: The readline function can produce some leaks, you don’t need to fix this. But beware your own code should not produce leaks. You should limit yourself to the subject description. Anything not asked is not required. For every point, if you have any doubt take bash as a reference.