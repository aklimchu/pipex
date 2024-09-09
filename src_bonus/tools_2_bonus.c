/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:12:18 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/09 09:07:35 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	free_double_arr(char **arr);

static int	word_count(char *str);

int	free_all(char **arr_1, char **arr_2, char *str, pid_t **pid)
{
	if (arr_1)
		free_double_arr(arr_1);
	if (arr_2)
		free_double_arr(arr_2);
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
	return (1);
}

static void	free_double_arr(char **arr)
{
	int		i;

	i = 0;
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
		arr = NULL;
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

int	count_param(char *str)
{
	int		i;

	i = 2;
	if (ft_strnstr(str, "grep", 4) && ft_strnstr(str, "-", 6) == 0)
		return (i);
	else
		return (word_count(str));
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
