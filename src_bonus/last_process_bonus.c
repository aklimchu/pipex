/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_process_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:48:04 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/03 14:27:16 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static int	open_dest_file(char *str, int pipe[2]);

int last_fork(t_fd *fd, char *argv[], char *envp[], int i)
{
	(*fd).pid[i] = fork();
	if ((*fd).pid[i] == -1)
	{
		perror("Fork failed");
		free((*fd).pid);
		(*fd).pid = NULL;
		return (1);
	}
	if ((*fd).pid[i] == 0)
		last_process(argv, envp, (*fd).pipe[i - 1], i + 2);
	close((*fd).pipe[i - 1][0]);
	//write end of pipe already closed?
	return (0);
}

void	last_process(char **argv, char **envp, int pipe[2], int i)
{
	int		fd_write;
	char	*path_2;
	char	**param_2;
	
	close(pipe[1]);
	
	fd_write = open_dest_file(argv[i + 1], pipe);
	
	if (dup2(pipe[0], 0) == -1 ||\
		dup2(fd_write, 1) == -1)
	{
		close_fds(pipe[0], fd_write, -1);
		perror("dup() error");
		exit(1);
	}

	close_fds(pipe[0], fd_write, -1);
	
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
	/* free_all(NULL, param_2, path_2);
	exit(0); */
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
/* 	else
		fd_write = open("/dev/stdout", O_WRONLY); */
	return (fd_write);
}