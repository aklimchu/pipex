/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:20:07 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/03 13:14:38 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	path_and_exec(char	**param_1, char **envp);

int pipe_and_fork(t_fd *fd, char *argv[], char *envp[], int i)
{
	if (i > 0 && (*fd).in != -1)
	{
		if (dup2((*fd).pipe[i - 1][0], (*fd).in) == -1)
		{
			close_fds((*fd).pipe[i - 1][0], (*fd).in, -1);
			perror("dup() error");
			return (1);
		}
	}
		//------------------opening the pipe----------------------------
		if (pipe((*fd).pipe[i]) == -1)
		{
			perror("Pipe failed");
			close_fds((*fd).in, -1, -1);
			if (i > 0)
				close((*fd).pipe[i - 1][0]);
			/* free((*fd).pid);
			(*fd).pid = NULL; */
			return (1);
		}
	
		//------------------forking------------------------------------
		(*fd).pid[i] = fork();
		if ((*fd).pid[i] == -1)
		{
			perror("Fork failed");
			close_fds((*fd).in, (*fd).pipe[i][0], (*fd).pipe[i][1]);
			if (i > 0)
				close((*fd).pipe[i - 1][0]);
/* 			free_pid(&(*fd).pid);
 */			return (1);
		}


		if ((*fd).pid[i] == 0)
			child_process(argv, envp, *fd, i);
		
		close((*fd).pipe[i][1]);
		if (i > 0)
			close((*fd).pipe[i - 1][0]);
		return (0);
}

void	child_process(char *argv[], char **envp, t_fd fd, int i)
{
	char	**param_1;
	
	close(fd.pipe[i][0]);
	
	if (fd.in == -1 && i == 0)
	{
		close(fd.pipe[i][1]);
		exit(1);
	}
	else if (fd.in != -1)
	{
		if (dup2(fd.in, 0) == -1)
		{
			close_fds(fd.pipe[i][1], fd.in, -1);
			if (i > 0)
				close(fd.pipe[i - 1][0]);
			perror("dup() error");
			exit(1);
		}
		close(fd.in);
	}
	else
		dup2(fd.pipe[i - 1][0], 0);
		
	if (i > 0)
		close(fd.pipe[i - 1][0]);
	
	if (dup2(fd.pipe[i][1], 1) == -1)
	{
		close_fds(fd.pipe[i][1], -1, -1);
		perror("dup() error");
		exit(1);
	}
	close(fd.pipe[i][1]);
				
	param_1 = check_param(argv[i + 2]);
	if (param_1 == NULL)
		exit(1);
	path_and_exec(param_1, envp);
}

static void	path_and_exec(char	**param_1, char **envp)
{
	char *path_1;
	
	path_1 = check_path(envp, param_1);
	if (path_1 == NULL)
	{
		free_all(param_1, NULL, NULL);
		exit(1);
	}
	if (execve(path_1, param_1, envp) == -1)
	{
		printing(param_1[0], ": Permission denied\n", 2);
		free_all(param_1, NULL, NULL);	// freeing path_1?
		exit(126);
	}
	/* free_all(param_1, NULL, path_1);
	exit(0); */
}