/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:48:04 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/02 08:46:47 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static int	child_process(char **argv, char **envp, t_fd fd);

int	fork_2(char **argv, char **envp, t_fd *fd)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		close_fds(-1, (*fd).pipe[0], (*fd).pipe[1]);	// writing end already closed?
		return(1);
	}
	if (pid == 0)
		child_process(argv, envp, *fd);
	close_fds(-1, (*fd).pipe[0], (*fd).pipe[1]);	// writing end already closed?
	waitpid(pid, &(*fd).status, 0);
	return(0);
}

static int	child_process(char **argv, char **envp, t_fd fd)
{
	int		fd_write;
	char	*path_2;
	char	**param_2;
	
	close(fd.pipe[1]);
	
	if (argv[4] && argv[4][0] == '\0')
	{
		printing(argv[4], ": No such file or directory\n", 2);
		close(fd.pipe[0]);
		exit(1);
	}
	else if (argv[4])
	{
		fd_write = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (fd_write == -1)
		{
			is_directory(argv[4]);
			if (access(argv[4], W_OK) == -1 && errno == EACCES)
				printing(argv[4], ": Permission denied\n", 2);
			close(fd.pipe[0]);
			exit(1);
		}
	}
	else
		fd_write = open("/dev/stdout", O_WRONLY);
	
	dup2(fd.pipe[0], 0);
	dup2(fd_write, 1);

	close_fds(-1, fd.pipe[0], fd_write);
	
	param_2 = check_param(argv[3]);
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