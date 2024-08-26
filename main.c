/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:39 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/26 15:47:59 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	p1;
	pid_t	p2;
	t_fd	fd;

	//--------------------checking the input-----------------------
	if (argc == 1)
		exit(0);

	
	//------------------opening the files---------------------------
	if (access(argv[1], R_OK) == -1 && errno == EACCES)
		ft_printf("pipex: %s: Permission denied\n", argv[1]);
	if (access(argv[1], F_OK) == -1 && errno == ENOENT)
		ft_printf("pipex: %s: No such file or directory\n", argv[1]);

	if (argc == 2)
		exit(0);
	
	fd.read = open(argv[1], O_RDONLY);

	//------------------opening the pipe----------------------------
	if (pipe(fd.pipe) == -1)
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

	fd.copy_out = dup(1);

	if (p1 == 0)
		child_process_1(argv, envp, fd.pipe, fd.read);
	close(fd.read);
	close(fd.pipe[1]);
	
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
		child_process_2(argv, envp, fd.pipe, fd.copy_out);
	
	close(fd.pipe[0]);
	close(fd.pipe[1]);
	close(fd.copy_out);
	
	waitpid(p2, &fd.status, 0);
	waitpid(p1, NULL, 0);
	if (WIFEXITED(fd.status))
	{
		fd.status = WEXITSTATUS(fd.status);
		exit(fd.status);
	}
	return (0);
}