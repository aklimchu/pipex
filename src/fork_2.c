/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:48:04 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/03 13:25:30 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	child_process(char **argv, char **envp, t_fd fd);

static int	open_dest_file(char *argv, int pipe[2]);

static void	path_and_exec(char	**param_2, char **envp);

int	fork_2(char **argv, char **envp, t_fd *fd)
{
	fd->p2 = fork();
	if (fd->p2 == -1)
	{
		perror("Fork failed");
		close_fds(-1, (*fd).pipe[0], (*fd).pipe[1]); // writing end already closed?
		return (1);
	}
	if (fd->p2 == 0)
		child_process(argv, envp, *fd);
	close_fds(-1, (*fd).pipe[0], (*fd).pipe[1]); // writing end already closed?
	//waitpid(fd->p2, &(*fd).status, 0);
	return (0);
}

static void	child_process(char **argv, char **envp, t_fd fd)
{
	char	**param_2;

	close(fd.pipe[1]);
	fd.write = open_dest_file(argv[4], fd.pipe);
	if (dup2(fd.pipe[0], 0) == -1 ||\
		dup2(fd.write, 1) == -1)
	{
		close_fds(fd.pipe[0], fd.write, -1);
		perror("dup() error");
		exit(1);
	}
	close_fds(fd.pipe[0], fd.write, -1);
	param_2 = check_param(argv[3]);
	if (param_2 == NULL)
		exit(1);
	path_and_exec(param_2, envp);
}

static int	open_dest_file(char *str, int pipe[2])
{
	int		fd_write;

	if (str && str[0] == '\0')
	{
		printing(str, ": No such file or directory\n", 2);
		close(pipe[0]);
		exit(1);
	}
	else /* if (str) */
	{
		fd_write = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (fd_write == -1)
		{
			is_directory(str);
			if (access(str, W_OK) == -1 && errno == EACCES)
				printing(str, ": Permission denied\n", 2);
			close(pipe[0]);
			exit(1);
		}
	}
	/* else
		fd_write = open("/dev/stdout", O_WRONLY); */
	return (fd_write);
}

static void	path_and_exec(char	**param_2, char **envp)
{
	char	*path_2;
	
	path_2 = check_path(envp, param_2);
	if (path_2 == NULL)
	{
		free_all(param_2, NULL, NULL);
		exit(1);
	}
	if (execve(path_2, param_2, envp) == -1)
	{
		printing(param_2[0], ": Permission denied\n", 2);
		free_all(param_2, NULL, NULL); // freeing path_2?
		exit(126);
	}
	/* free_all(NULL, param_2, path_2);
	exit(0); */
}