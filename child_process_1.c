/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:20:07 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/26 13:46:06 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_1(char **argv, char **envp, int *fd_pipe, int fd_read)
{
	char	*path_1;
	char	**param_1;
	
	close(fd_pipe[0]);
	
	if (fd_read == -1)
		exit(1);

	dup2(fd_read, 0);
	dup2(fd_pipe[1], 1);

	close(fd_read);
	close(fd_pipe[1]);
				
	param_1 = check_param(argv[2], 2);
	if (param_1 == NULL)
	{
		exit(1);
	}
	path_1 = check_path(envp, param_1, 2);
	if (path_1 == NULL)
	{
		free_all(param_1, NULL, NULL);
		exit(1);
	}
	if (execve(path_1, param_1, envp) == -1)
	{
		printing(param_1[0], ": Permission denied\n", 2);
		free_all(param_1, NULL, NULL);	// freeing path_1?
		exit(126);
	}
	free_all(param_1, NULL, path_1);
	exit(0);
}