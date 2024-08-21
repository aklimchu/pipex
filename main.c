/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:39 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/21 14:10:19 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	p1;
	pid_t	p2;
	int		fd_read;
	int		status;
	int copy_out = dup(1);	// delete?
	
	//--------------------checking the input-----------------------
	if (argc == 1)
		exit(0);

	//------------------opening the files---------------------------
	if (access(argv[1], R_OK) == -1 && errno == EACCES)
		ft_printf("pipex: permission denied: %s\n", argv[1]);
	if (access(argv[1], F_OK) == -1 && errno == ENOENT)
		ft_printf("pipex: no such file or directory: %s\n", argv[1]);

	if (argc == 2)
		exit(0);
	
	fd_read = open(argv[1], O_RDONLY);

	/* if (fd_read == -1)
	{
		perror("Opening the input file failed");
		exit(1);
	} */

	//------------------opening the pipe----------------------------
	if (pipe(fd) == -1)
	{
		perror("Pipe failed");
		exit(1);
	}

	//------------------first fork----------------------------------
	p1 = fork();
	if (p1 == -1)
	{
		perror("Fork failed");
		exit(1);
	}

	if (p1 == 0)
		child_process_1(argv, envp, fd, fd_read, copy_out);
	close(fd_read);
	close(fd[1]);
	
	//char *inbuf;	//?

	if (argc == 3)
		exit(0);
	
	//------------------second fork----------------------------------
	p2 = fork();
	if (p2 == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	if (p2 == 0) 
		child_process_2(argv, envp, fd, copy_out);
	//waitpid(p1, NULL, 0);	causes timeout?
	waitpid(p2, &status, 0);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		exit(status);
	}
	return (0);
}