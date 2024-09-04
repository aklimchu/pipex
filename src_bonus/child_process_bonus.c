/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:20:07 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/04 10:48:54 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	fd_in_dup(t_fd fd, int i);

static void	path_and_exec(char	**param_1, char **envp, t_fd fd);

int	pipe_and_fork(t_fd *fd, char *argv[], char *envp[], int i)
{
	if (i > 0 && (*fd).in != -1 && dup2((*fd).pipe[i - 1][0], (*fd).in) == -1) // will it work correctly?
	{
		perror("dup() error");
		return (close_free((*fd).pipe[i - 1][0], (*fd).in, -1, &(*fd).null));
	}
	if (pipe((*fd).pipe[i]) == -1) // opening the pipe
	{
		perror("Pipe failed");
		if (i > 0)
			close((*fd).pipe[i - 1][0]);
		return (close_free((*fd).in, -1, -1, &(*fd).null));
	}
	(*fd).pid[i] = fork(); // forking
	if ((*fd).pid[i] == -1)
	{
		perror("Fork failed");
		if (i > 0)
			close((*fd).pipe[i - 1][0]);
		return (close_free((*fd).in, (*fd).pipe[i][0], (*fd).pipe[i][1], &(*fd).null));
	}
	if ((*fd).pid[i] == 0)
		child_process(argv, envp, *fd, i); // child process
	if (i > 0)
		close((*fd).pipe[i - 1][0]);
	return (close((*fd).pipe[i][1]));
}

void	child_process(char *argv[], char **envp, t_fd fd, int i)
{
	char	**param_1;

	close(fd.pipe[i][0]);
	if (fd.in == -1 && i == 0)
	{
		//close(fd.pipe[i][1]);
		//free_pid(&fd.pid); //new
		close_free(fd.pipe[i][1], -1, -1, &fd.pid);
		exit(1);
	}
	else if (fd.in != -1)
		fd_in_dup(fd, i);
	else
		dup2(fd.pipe[i - 1][0], 0);
	if (i > 0)
		close(fd.pipe[i - 1][0]);
	if (dup2(fd.pipe[i][1], 1) == -1)
	{
		close_free(fd.pipe[i][1], -1, -1, &fd.pid);
		//free_pid(&fd.pid); // new
		perror("dup() error");
		exit(1);
	}
	close(fd.pipe[i][1]);
	param_1 = check_param(argv[i + 2], fd);
	if (param_1 == NULL)
	{
		free_pid(&fd.pid);
		exit(1);
	}
	path_and_exec(param_1, envp, fd);
	//free_pid(&fd.pid); // do we need?
}

static void	fd_in_dup(t_fd fd, int i)
{
	if (dup2(fd.in, 0) == -1)
	{
		close_free(fd.pipe[i][1], fd.in, -1, &fd.pid);
		if (i > 0)
			close(fd.pipe[i - 1][0]);
		perror("dup() error");
		exit(1);
	}
	close(fd.in);
}

static void	path_and_exec(char	**param_1, char **envp, t_fd fd)
{
	char	*path_1;

	path_1 = check_path(envp, param_1, fd);
	if (path_1 == NULL)
	{
		free_all(param_1, NULL, NULL, &fd.pid);
		exit(1);
	}
	// do we need to free pids here?
	if (execve(path_1, param_1, envp) == -1)
	{
		printing(param_1[0], ": Permission denied\n", 2);
		free_all(param_1, NULL, NULL, &fd.pid); // freeing path_1?
		exit(126);
	}
	/* free_all(param_1, NULL, path_1);
	exit(0); */
}
