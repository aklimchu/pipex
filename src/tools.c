/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:20:10 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/04 11:35:31 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static size_t	checkc(char c, char const *set);

static size_t	checklen(char const *s1, char const *set);

//The function checks if provided link is a directory
int	is_directory(char *path, int fd_pipe, char **param)
{
	int		fd;
	char	buffer;
	ssize_t	result;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	result = read(fd, &buffer, 1);
	if (result < 0 && errno == EISDIR)
	{
		printing(path, ": Is a directory\n", 2);
		close_fds(fd, fd_pipe, -1);
		free_all(param, NULL, NULL);
		exit(126);
	}
	close(fd);
	return (0);
}

//The function filters out selected symbols from the string provided by user
char	*str_filter(char *s1, char *set)
{
	size_t	newlen;
	char	*new_s;

	newlen = checklen(s1, set);
	new_s = (char *)malloc((newlen + 1) * sizeof(char));
	if (new_s == NULL)
		return ((void *)0);
	while (*s1)
	{
		if (checkc(*s1, set) == 1)
			s1++;
		else if (checkc(*s1, set) == 0)
		{
			*new_s = *s1;
			new_s++;
			s1++;
		}
	}
	*new_s = '\0';
	return (new_s - newlen);
}

//The function checks if character c is part of the set
static size_t	checkc(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

//The function calculates the length of a new string
//formed as a result of filtering out the characters from the set
static size_t	checklen(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (*s1)
	{
		if (checkc(*s1, set) == 1)
			s1++;
		else if (checkc(*s1, set) == 0)
		{
			s1++;
			i++;
		}
	}
	return (i);
}
