/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_process_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:48:04 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/29 10:53:57 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	last_process(char **argv, char **envp, int pipe[2], int i)
{
	int		fd_write;
	char	*path_2;
	char	**param_2;
	
	close(pipe[1]);
	
	if (argv[i + 1] && argv[i + 1][0] == '\0')
	{
		printing(argv[i + 1], ": No such file or directory\n", 2);
		close(pipe[0]);
		exit(1);
	}
	else if (argv[i + 1])
	{
		fd_write = open(argv[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (fd_write == -1)
		{
			is_directory(argv[i + 1]);
			if (access(argv[i + 1], W_OK) == -1 && errno == EACCES)
				printing(argv[i + 1], ": Permission denied\n", 2);
			close(pipe[0]);
			exit(1);
		}
	}
	else
		fd_write = open("/dev/stdout", O_WRONLY);
	
	dup2(pipe[0], 0);
	dup2(fd_write, 1);

	close_fds(-1, pipe[0], fd_write);
	
	param_2 = check_param(argv[i]);
	if (param_2 == NULL)
		exit(1);
		
	path_2 = check_path(envp, param_2);
	if (path_2 == NULL)
	{
		free_all(param_2, NULL, NULL);
		exit(1);
	}
	if (execve(path_2, param_2, envp) == -1)
	{
		printing(param_2[0], ": Permission denied\n", 2);
		free_all(param_2, NULL, NULL);	// freeing path_2?
		exit(126);
	}
	free_all(NULL, param_2, path_2);
	exit(0);
}