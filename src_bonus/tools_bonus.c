/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:20:10 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/04 11:10:42 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static size_t	checkc(char c, char const *set);

static size_t	checklen(char const *s1, char const *set);

void	check_command_access(char **param, t_fd fd)
{
	char	*command;

	command = param[0];
	if (access(command, F_OK) == -1 && errno == ENOENT)
	{
		printing(command, ": No such file or directory\n", 2);
		free_all(param, NULL, NULL, &fd.pid);
		exit(127);
	}
}

int	is_directory(char *path, t_fd fd, int fd_pipe, char **param)
{
	int		test_fd;
	char	buffer;
	ssize_t	result;

	test_fd = open(path, O_RDONLY);
	if (test_fd < 0)
		return (-1);
	result = read(test_fd, &buffer, 1);
	if (result < 0 && errno == EISDIR)
	{
		printing(path, ": Is a directory\n", 2);
		close_free(test_fd, fd_pipe, -1, &fd.pid);
		free_all(param, NULL, NULL, &fd.null);
		exit(126);
	}
	close(test_fd);
	return (0);
}

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
