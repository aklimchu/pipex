/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 09:14:14 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/02 08:08:07 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_all(char **arr_1, char **arr_2, char *str)
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
}

void	close_fds(int fd1, int fd2, int fd3)
{
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
	if (fd3 >= 0)
		close(fd3);
}