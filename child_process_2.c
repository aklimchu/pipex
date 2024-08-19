/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:48:04 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/19 15:01:08 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_process_2(char **argv, char **envp, int *fd, int copy_out)
{
	int		fd_write;
	char	*path_2;
	char	**param_2;
	
	(void)copy_out; // delete copy_out 
	
	close(fd[1]);
	
/* 	write(copy_out, "Child 2\n", 8);
 */
	fd_write = open(argv[4], O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd_write == -1 && access(argv[4], W_OK) == -1 && errno == EACCES)
	{
		ft_printf("pipex: %s: permission denied\n", argv[4]);
		close(fd[0]);
		close(fd_write);
		exit(1);
	}
	/* if (fd_write == -1)
	{
		perror("Opening the output file failed");
		//close fds
		exit(1);
	} */
	
	dup2(fd[0], 0);
	dup2(fd_write, 1);

	close(fd[0]);
	close(fd_write);
	
	param_2 = check_param(argv[3]);
	if (param_2 == NULL)
	{
		//close fds
		exit(1);
	}
	path_2 = check_path(envp, param_2, copy_out);	//error checking
	if (path_2 == NULL)
	{
		free_all(param_2, NULL, NULL);
		//close fds
		exit(1);
	}
	if (execve(path_2, param_2, envp) == -1)
	{
		perror("Command 2 failed");
		free_all(NULL, param_2, path_2);
		//close fds
		exit(1);
	}
	free_all(NULL, param_2, path_2);
	close(fd[0]);
	exit(0);
}