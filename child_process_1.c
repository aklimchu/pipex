/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:20:07 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/19 14:59:12 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_1(char **argv, char **envp, int *fd, int fd_read, int copy_out)
{
	char	*path_1;
	char	**param_1;
	
	close(fd[0]);
	
	if (fd_read == -1)
		exit(1);

	dup2(fd_read, 0);
	dup2(fd[1], 1);

	close(fd_read);
	close(fd[1]);
				
	param_1 = check_param(argv[2]);
	if (param_1 == NULL)
	{
		//close fds
		exit(1);
	}
	path_1 = check_path(envp, param_1, copy_out);
	if (path_1 == NULL)
	{
		//close fds
		free_all(param_1, NULL, NULL);
		exit(1);
	}
	if (check_error_cmd(param_1, path_1, argv[1], 1) == 0) // cmd ?
	{
		if (execve(path_1, param_1, envp) == -1)
		{
			perror("Command 1 failed");
			free_all(param_1, NULL, path_1);
			//close fds
			exit(1);
		}
	}
	free_all(param_1, NULL, path_1);
	exit(0);
}