/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:12:18 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/04 10:53:29 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static int	word_count(char *str);

int	count_param(char *str)
{
	int		i;

	i = 2;
	if (ft_strnstr(str, "grep", 4) && ft_strnstr(str, "-", 6) == 0)
		return (i);
	else
		return (word_count(str));
}

void	check_command_access(char **param, t_fd fd)
{
	char	*command;

	command = param[0];
	/* if (access(command, X_OK) == -1 && errno == EACCES)
	{
		printing(command, "Permission denied", 2);
		free_all(param, NULL, NULL, copy_out);
		exit(126);
	} */
	if (access(command, F_OK) == -1 && errno == ENOENT)
	{
		printing(command, ": No such file or directory\n", 2);
		free_all(param, NULL, NULL, &fd.pid);
		exit(127);
	}
}

void	free_all(char **arr_1, char **arr_2, char *str, pid_t **pid)
{
	int		i;

	i = 0;
	if (arr_1)
	{
		while (arr_1[i])
			free(arr_1[i++]);
		free(arr_1);
		arr_1 = NULL;
	}
	i = 0;
	if (arr_2)
	{
		while (arr_2[i])
			free(arr_2[i++]);
		free(arr_2);
		arr_2 = NULL;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
	if (*pid)
	{
		free(*pid);
		*pid = NULL;
	}
}

int	close_free(int fd1, int fd2, int fd3, pid_t **pid)
{
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
	if (fd3 >= 0)
		close(fd3);
	if (*pid)
	{
		free(*pid);
		*pid = NULL;
	}
	return (1);
}

static int	word_count(char *str)
{
	int		count;
	int		flag;

	count = 1;
	flag = 0;
	while (*str)
	{
		if (*str == '{')
			flag = 1;
		if (*str == '}')
			flag = 0;
		if (*str == ' ' && *(str + 1) != ' ' && flag == 0)
			count++;
		str++;
	}
	return (count);
}
