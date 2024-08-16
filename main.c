/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:39 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/16 13:10:13 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	p1;
	pid_t	p2;
	int		fd_read;
	int		fd_write;
	char	*path_1;
	char	*path_2;
	char	**param_1;
	char	**param_2;
	int copy_out = dup(1);// delete
	(void)copy_out;
	
	//--------------------checking the input-----------------------
	if (argc > 5)
	{
		perror("Too many arguments\n");
		exit(1);
	}
	if (argc < 5)
	{
		perror("Not enough arguments\n");
		exit(1);
	}

	//------------------opening the files---------------------------
	fd_read = open(argv[1], O_RDONLY);
	if (fd_read == -1)
	{
		perror("Opening the input file failed");
		exit(1);
	}

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
	if (p1 == 0) // child process
	{
		close(fd[0]);	//new

		dup2(fd_read, 0);
		dup2(fd[1], 1);

		close(fd_read);	// new
		close(fd[1]);// new
				
		param_1 = check_param(argv[2]);
		/* int i = 0;
		while (param_1[i])
			ft_printf("param_1 %s\n", param_1[i++]); */
		path_1 = check_path(envp, param_1[0]);
		if (execve(path_1, param_1, envp) == -1)
		{
			perror("Command 1 failed");
			free(path_1);	//+free param_1
			exit(1);
		}


		/* close(0);
		close(1); */
	}
	//waitpid(0, NULL, 0);
	/* close(0);
	close(1); */
	close(fd_read);	//new
	close(fd[1]);	//new

	//------------------second fork----------------------------------
	p2 = fork();
	if (p2 == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	if (p2 == 0) // child process
	{
		close(fd[1]);	// new
		
		fd_write = open(argv[4], O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (fd_write == -1)
		{
			perror("Opening the output file failed");
			exit(1);
		}
		
		dup2(fd[0], 0);
		dup2(fd_write, 1);

		close(fd[0]);	// new
		close(fd_write);// new
		//dup2(copy_out, 1);
		//write(1, "c", 1);
		/* (void)param_2;
		(void)path_2; */
		param_2 = check_param(argv[3]);
		/*int i = 0;
		while (param_2[i])
			ft_printf("param_2 %s\n", param_2[i++]); */
		path_2 = check_path(envp, param_2[0]);
		if (execve(path_2, param_2, envp) == -1)
		{
			perror("Command 2 failed");
			free(path_2);	//+free param_2
			exit(1);
		}
		/* close(0);
		close(1); */
		close(fd[0]);	//new
	}
	waitpid(p1, NULL, 0);
	waitpid(p2, NULL, 0);
	/* close(0); */
	return (0);
}