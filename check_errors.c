/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:39:10 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/19 12:09:13 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_error_cmd(char **param, char *path, char *name, int flag)
{
	// access
	if (access(path, F_OK) == -1 && errno == EACCES)
	{
		ft_printf("pipex: %s: permission denied\n", name);
		if (flag == 2)	// second command
		{
			free_all(param, NULL, path);
			exit(1);
		}
		return (1);
	}
	// no file
	if (access(path, F_OK) == -1 && errno == ENOENT)
	{
		ft_printf("pipex: %s: no such file or directory\n", name);
		return (1);
	}
	return (0);
}

/* int	check_error_file_2(char **param, char *path, char *name)
{
	// access
	if (access(path, F_OK) == -1 && errno == EACCES)
	{
		ft_printf();
		free_all(param, NULL, path);
		exit( );
	}
	// no file
	if (access(path, F_OK) == -1 && errno == ENOENT)
	{
		ft_printf();
		free_all(param, NULL, path);
		exit( );
	}
	return (0);
} */