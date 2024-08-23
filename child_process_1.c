/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:20:07 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/23 09:01:17 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_1(char **argv, char **envp, int *fd, int fd_read, int copy_out)
{
	char	*path_1;
	char	**param_1;
	
	(void)copy_out;

	close(fd[0]);
	
	if (fd_read == -1)
		exit(1);

	dup2(fd_read, 0);
	dup2(fd[1], 1);

	close(fd_read);
	close(fd[1]);
				
	param_1 = check_param(argv[2], copy_out);
	if (param_1 == NULL)
	{
		exit(1);
	}
	path_1 = check_path(envp, param_1, copy_out);
	if (path_1 == NULL)
	{
		free_all(param_1, NULL, NULL);
		exit(1);
	}
	if (check_error_cmd(param_1, path_1, argv[1], 1) == 0) // do we need?
	{
		if (execve(path_1, param_1, envp) == -1)
		{
			printing(param_1[0], ": Permission denied\n", 2);
			free_all(param_1, NULL, NULL);	// freeing path_1?
			exit(126);
		}
	}
	free_all(param_1, NULL, path_1);
	exit(0);
}