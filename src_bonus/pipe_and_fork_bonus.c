/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:20:07 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/05 13:25:49 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	fd_in_dup(t_fd fd);

static void	path_and_exec(char	**param_1, char **envp, t_fd fd);

int	pipe_and_fork(t_fd *fd, char *argv[], char *envp[], int i)
{
	if (pipe(fd->pipe) == -1)
	{
		perror("Pipe failed");
		return (close_free(fd->in, -1, -1, &fd->null));
	}
	fd->pid[i] = fork();
	if (fd->pid[i] == -1)
	{
		perror("Fork failed");
		return (close_free(fd->in, fd->pipe[0], fd->pipe[1], &fd->null));
	}
	if (fd->pid[i] == 0)
		child_process(argv, envp, *fd, i);
	if (dup2(fd->pipe[0], 0) == -1)
	{
		close_free(fd->in, fd->pipe[0], fd->pipe[1], &fd->null);
		perror("dup() error");
		exit(1);
	}
	close_free(fd->in, fd->pipe[0], fd->pipe[1], &fd->null);
	return (0);
}

void	child_process(char *argv[], char **envp, t_fd fd, int i)
{
	char	**param_1;

	close(fd.pipe[0]);
	if (fd.in == -1 && i == 0)
	{
		close_free(-1, fd.pipe[1], -1, &fd.pid);
		exit(1);
	}
	else if (fd.in != -1 && i == 0)
		fd_in_dup(fd);
	if (dup2(fd.pipe[1], 1) == -1)
	{
		close_free(-1, fd.pipe[1], -1, &fd.pid);
		perror("dup() error");
		exit(1);
	}
	close(fd.pipe[1]);
	param_1 = check_param(argv[i + 2 + fd.hd_flag], fd);
	if (param_1 == NULL)
	{
		free_pid(&fd.pid);
		exit(1);
	}
	path_and_exec(param_1, envp, fd);
}

static void	fd_in_dup(t_fd fd)
{
	if (dup2(fd.in, 0) == -1)
	{
		close_free(fd.in, fd.pipe[1], -1, &fd.pid);
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
	if (execve(path_1, param_1, envp) == -1)
	{
		printing(param_1[0], ": Permission denied\n", 2);
		free_all(param_1, NULL, NULL, &fd.pid);
		exit(126);
	}
}
