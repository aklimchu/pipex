/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_fork_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:48:04 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/09 08:22:00 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	dup_tools(t_fd fd);

static int	open_dest_file(char *str, int pipe[2], t_fd fd);

//The function creates the fork and then enter the last child process
int	last_fork(t_fd *fd, char *argv[], char *envp[], int i)
{
	fd->pid[i] = fork();
	if (fd->pid[i] == -1)
	{
		perror("Fork failed");
		free_pid(&fd->pid);
		return (1);
	}
	if (fd->pid[i] == 0)
		last_process(argv, envp, *fd, i + 2);
	return (0);
}

//Child process where user command is called from the last user command
void	last_process(char **argv, char **envp, t_fd fd, int i)
{
	char	*path_2;
	char	**param_2;

	close(fd.pipe[1]);
	fd.out = open_dest_file(argv[i + 1 + fd.hd_flag], fd.pipe, fd);
	dup_tools(fd);
	close_free(-1, -1, fd.out, &fd.null);
	param_2 = check_param(argv[i + fd.hd_flag], fd);
	if (param_2 == NULL)
	{
		free_pid(&fd.pid);
		exit(1);
	}
	path_2 = check_path(envp, param_2, fd);
	if (path_2 == NULL)
	{
		free_all(param_2, NULL, NULL, &fd.pid);
		exit(1);
	}
	if (execve(path_2, param_2, envp) == -1)
	{
		printing(param_2[0], ": Permission denied\n", 2);
		free_all(param_2, NULL, NULL, &fd.pid);
		exit(126);
	}
}

//Helper function duplucates file descriptor of destination file to stdout
static void	dup_tools(t_fd fd)
{
	if (dup2(fd.out, 1) == -1)
	{
		close_free(-1, -1, fd.out, &fd.pid);
		perror("dup() error");
		exit(1);
	}
}

//The function opens the the destination file and returns
//a file descriptor to it
static int	open_dest_file(char *str, int pipe[2], t_fd fd)
{
	int		fd_write;

	if (str && str[0] == '\0')
	{
		printing(str, ": No such file or directory\n", 2);
		close_free(-1, pipe[0], -1, &fd.pid);
		exit(1);
	}
	else
	{
		fd_write = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (fd_write == -1)
		{
			is_directory(str, fd, pipe[0], NULL);
			if (access(str, W_OK) == -1 && errno == EACCES)
				printing(str, ": Permission denied\n", 2);
			close_free(-1, pipe[0], -1, &fd.pid);
			exit(1);
		}
	}
	return (fd_write);
}
