/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:20:07 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/02 09:37:23 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	child_process(char **argv, char **envp, t_fd fd);

static void	path_and_exec(char	**param_1, char **envp);

int	fork_1(char **argv, char **envp, t_fd *fd)
{
	fd->p1 = fork();
	if (fd->p1 == -1)
	{
		perror("Fork failed");
		close_fds((*fd).read, (*fd).pipe[0], (*fd).pipe[1]);
		return (1);
	}
	if (fd->p1 == 0)
		child_process(argv, envp, (*fd));
	close_fds((*fd).read, -1, (*fd).pipe[1]);
	//waitpid(fd->p1, NULL, 0);
	return (0);
}

static void	child_process(char **argv, char **envp, t_fd fd)
{
	char	**param_1;
<<<<<<< HEAD:src/child_process_1.c
	
	//modified
	
=======

>>>>>>> f162a6e469fdebd97db05638b6ccd06a9c7a132d:src/fork_1.c
	close(fd.pipe[0]);
	if (fd.read == -1)
	{
		close(fd.pipe[1]);
		exit(1);
	}
	dup2(fd.read, 0);
	dup2(fd.pipe[1], 1);
	close_fds(fd.read, -1, fd.pipe[1]);
	param_1 = check_param(argv[2]);
	if (param_1 == NULL)
		exit(1);
	path_and_exec(param_1, envp);
}

static void	path_and_exec(char	**param_1, char **envp)
{
	char	*path_1;

	path_1 = check_path(envp, param_1);
	if (path_1 == NULL)
	{
		free_all(param_1, NULL, NULL);
		exit(1);
	}
	if (execve(path_1, param_1, envp) == -1)
	{
		printing(param_1[0], ": Permission denied\n", 2);
		free_all(param_1, NULL, NULL); // freeing path_1?
		exit(126);
	}
	free_all(param_1, NULL, path_1);
	exit(0);
}
