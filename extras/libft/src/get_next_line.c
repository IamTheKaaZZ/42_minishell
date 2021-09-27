/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:22:15 by bcosters          #+#    #+#             */
/*   Updated: 2021/06/18 17:44:32 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

/*
**	BOOLEAN to check edge cases
**	RETURNS:
**	(1)	Handle edge case where:
**		(retval != 0) OR (saved[fd] is empty) OR (saved[fd] contains only '\0')
**		IF: EOF AND no line added by previous processes
**		- Fill line with either buff (if saved[fd] is empty) or saved[fd]
**		- free buff
**	(0) No edge case
*/

static int	edge_cases(int retval, char **s, char **line, char *buff)
{
	if (retval != 0 || *s == NULL || *s[0] == '\0')
	{
		if (!retval && !*line)
		{
			if (!*s)
				*line = ft_strdup(buff);
			else
				*line = ft_strdup(*s);
		}
		free(buff);
		return (1);
	}
	return (0);
}

/*
**	BOOLEAN to handle error cases
**	RETURNS:
**	(1)	Possible errors:
**		- line does not exist
**		- file descriptor is out of range
**		- Invalid file descriptor
**		- invalid buffersize for read
**	(0)	No error case
*/

static int	error_cases(int fd, char **line, char **s)
{
	if (!line || (fd < 0 || fd >= MAX_FD) || (read(fd, s[fd], 0) < 0)
		|| BUFFER_SIZE < 1)
		return (1);
	return (0);
}

/*
**	BOOLEAN that tries to add a line
**		Set temp = saved[fd]
**		Set tokeep = NULL
**	RETURNS:
**	(0)	No '\n' found in saved[fd] or EOF reached
**		- EOF line gets handled in edge_cases
**	(1)	'\n' has been found in saved[fd]
**		- replace '\n' on found index to a '\0'
**		- Add a line with everything before that new '\0'
**		- IF next index != '\0' AKA EOF
**			keep what's left and store it in saved[fd]
**		- ELSE: set saved[fd] to tokeep AKA NULL
**		- Free temp and set it to NULL
*/

static int	addline(char **s, char **line)
{
	int		i;
	char	*temp;
	char	*tokeep;

	i = 0;
	temp = *s;
	tokeep = NULL;
	while (temp[i] != '\n')
	{
		if (!temp[i++])
			return (0);
	}
	temp[i] = '\0';
	*line = ft_strdup(temp);
	if (temp[i + 1] != '\0')
		tokeep = ft_strdup(&temp[i + 1]);
	*s = tokeep;
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	return (1);
}

/*
**	Function to determine the retval of GNL
**	LOOP: retval = read to buff until EOF or breakpoint
**	1.	NULL-terminate buff after a read
**	2.	IF saved[fd] is empty:
**			- Store contents of buff in it
**		ELSE:
**			- Store saved[fd] in temp
**			- Reset saved[fd] as the joined string of temp and buff
**			- Free temp and set it to NULL
**	3.	Check if a line can be made
**			- YES: break the loop
**			- NO: continue reading
**	RETURNS:
**		(1)	IF retval > 0
**		(0)	IF retval == 0 AKA EOF
*/

static int	readfile(int fd, char *buff, char **saved, char **line)
{
	int		retval;
	char	*temp;

	retval = read(fd, buff, BUFFER_SIZE);
	while (retval > 0)
	{
		buff[retval] = '\0';
		if (*saved == NULL)
			*saved = ft_strdup(buff);
		else
		{
			temp = *saved;
			*saved = ft_strjoin(temp, buff);
			free(temp);
			temp = NULL;
		}
		if (addline(saved, line))
			break ;
		retval = read(fd, buff, BUFFER_SIZE);
	}
	return ((retval > 0));
}

/*
**	1.	error_cases: does line exist/is fd valid/BUFFER_SIZE valid/malloc?
**	2.	Is there content saved from a previous call?
**		AND can we make a line out of it?
**			YES: Process what is there and free buff, return 1
**			NO: Continue
**	3.	Fill buff with '\0'
**	4.	Call readfile to read, make a line if possible and save what's left
**	5.	handle edge_cases depending on retval, what is saved etc.
**	6.	If no edge cases: Add the line, empty saved, free buff and return
*/

int	get_next_line(int fd, char **line)
{
	int			i;
	int			retval;
	static char	*saved[MAX_FD];
	char		*buff;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (error_cases(fd, line, saved) || !(buff))
		return (-1);
	if (saved[fd] && addline(&saved[fd], line))
	{
		free(buff);
		return (1);
	}
	i = 0;
	while (i < BUFFER_SIZE)
		buff[i++] = '\0';
	retval = readfile(fd, buff, &saved[fd], line);
	if (edge_cases(retval, &saved[fd], line, buff))
		return (retval);
	*line = saved[fd];
	saved[fd] = NULL;
	free(buff);
	return (retval);
}
