/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:39 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/02 08:08:59 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	*pid;	// do we need array of pid if every fork is handled inside own function?
	// now a problem with freeing in some cases
	t_fd	fd;
	int		i;
	
	//--------------------checking the input-----------------------
	if (argc == 1)
		return(1);
	
	//------------------opening the files---------------------------
	if (access(argv[1], R_OK) == -1 && errno == EACCES)
		ft_printf("pipex: %s: Permission denied\n", argv[1]);
	if (access(argv[1], F_OK) == -1 && errno == ENOENT)
		ft_printf("pipex: %s: No such file or directory\n", argv[1]);
	
	if (argc == 2)
		return(1);
	
	if (argc > 4)
		pid = malloc((argc - 3) * sizeof(pid_t));
	else
		pid = malloc((argc - 2) * sizeof(pid_t));
	if (pid == NULL)
		return(1);
	
	fd.in = open(argv[1], O_RDONLY);

	i = 0;
	while (i == 0 || i < argc - 4)
	{
		if (i > 0 && fd.in != -1)
			dup2(fd.pipe[i - 1][0], fd.in);
				
		//------------------opening the pipe----------------------------
		if (pipe(fd.pipe[i]) == -1)
		{
			perror("Pipe failed");
			close_fds(fd.in, -1, -1);
			if (i > 0)
				close(fd.pipe[i - 1][0]);
			free(pid);
			pid = NULL;
			return(1);
		}
	
		//------------------forking------------------------------------
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("Fork failed");
			close_fds(fd.in, fd.pipe[i][0], fd.pipe[i][1]);
			if (i > 0)
				close(fd.pipe[i - 1][0]);
			free(pid);
			pid = NULL;
			return(1);
		}


		if (pid[i] == 0)
			child_process(argv, envp, fd, i);
		
		close(fd.pipe[i][1]);
		if (i > 0)
			close(fd.pipe[i - 1][0]);
		i++;
	}

	close_fds(fd.in, -1, -1);

	if (argc == 3)
	{
		close(fd.pipe[i - 1][0]);
		free(pid);
		pid = NULL;
		return(1);
	}
	
	//------------------last fork----------------------------------
		
	pid[i] = fork();
	if (pid[i] == -1)
	{
		perror("Fork failed");
		free(pid);
		pid = NULL;
		return(1);
	}
	if (pid[i] == 0)
		last_process(argv, envp, fd.pipe[i - 1], i + 2);
	close(fd.pipe[i - 1][0]);
	//write end of pipe already closed?
	
	waitpid(pid[i], &fd.status, 0);
	i = 0;
	while (i < argc - 4)
		waitpid(pid[i++], NULL, 0);
	free(pid);
	pid = NULL;
	if (WIFEXITED(fd.status))
		return (WEXITSTATUS(fd.status));
	return (0);
}