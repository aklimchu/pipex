/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:39 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/29 16:57:22 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid[1024];	//change? pid_t *pid = malloc((argc - 3) * sizeof(pid_t));
	t_fd	fd;
	int		i;

	//--------------------checking the input-----------------------
	if (argc == 1)
		return(1);

	
	//------------------opening the files---------------------------
	if (access(argv[1], R_OK) == -1 && errno == EACCES)
		ft_printf("pipex: %s: Permission denied\n", argv[1]);
	if (access(argv[1], F_OK) == -1 && errno == ENOENT)
	{
		ft_printf("pipex: %s: No such file or directory\n", argv[1]);
	}
	if (argc == 2)
		return(1);
	
	fd.in = open(argv[1], O_RDONLY);

	i = 0;
	while (i == 0 || i < argc - 4)
	{
		if (i > 0)
		{
			if (fd.in != -1)
				dup2(fd.pipe[i - 1][0], fd.in);	// invalid file descriptor?
			close(fd.pipe[i - 1][0]);
		}
		//------------------opening the pipe----------------------------
		if (pipe(fd.pipe[i]) == -1)
		{
			perror("Pipe failed");
			close(fd.in);
			return(1);
		}
	
		//------------------forking------------------------------------
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("Fork failed");
			close_fds(fd.in, fd.pipe[i][0], fd.pipe[i][1]);
			return(1);
		}


		if (pid[i] == 0)
			child_process(/*argv[i + 2]*/argv, envp, fd, i/*fd.in, fd.pipe[i]*/);
		
		close_fds(/* fd.in */ -1, -1, fd.pipe[i][1]);

		i++;
	}

	if (fd.in != -1)
		close(fd.in);

	if (argc == 3)
	{
		close(fd.pipe[i - 1][0]);
		return(1);
	}
	
	//------------------last fork----------------------------------
	
	/* if (pipe(fd.pipe[i]) == -1)
	{
		perror("Pipe failed");
		close(fd.in);
		return(1);
	} */
	
	pid[i] = fork();
	if (pid[i] == -1)
	{
		perror("Fork failed");
		return(1);
	}
	if (pid[i] == 0)
		last_process(argv, envp, fd.pipe[i - 1], i + 2);
	close_fds(-1, fd.pipe[i - 1][0], -1 /* fd.pipe[i - 1][1] */);
	//write end of pipe already closed?
	
	// what if there is no outfile (argc - ?)?

	waitpid(pid[i], &fd.status, 0);	// changed, was argc - 3
	i = 0;
	while (i < argc - 4)	// changed, was argc - 4
		waitpid(pid[i++], NULL, 0);
	if (WIFEXITED(fd.status))
		return (WEXITSTATUS(fd.status));
	return (0);
}