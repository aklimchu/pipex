#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	int		nbytes;
	pid_t	p1;
	pid_t	p2;
	int		fd_read;
	int		fd_write;

	(void)envp;
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
		perror("Opening the file failed");
		exit(1);
	}
	fd_write = open(argv[4], O_WRONLY);
	if (fd_write == -1)
	{
		perror("Opening the file failed");
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
		char buffer[BUFFER_PIPEX];
		
		//------------------opening the pipe----------------------------
		if (pipe(fd) == -1)
		{
			perror("Pipe failed");
			exit(1);
		}
		dup2(fd_read, 0);
		dup2(fd[1], 1);
		nbytes = read(0, buffer, BUFFER_PIPEX);
		if (nbytes == -1)
			exit(1);
		// command 1
		write(1, buffer, BUFFER_PIPEX);
		close(0);
	}
	
	//------------------second fork----------------------------------
	p2 = fork();
	if (p2 == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	if (p2 == 0) // child process
	{
		char buffer_2[BUFFER_PIPEX];
		
		dup2(fd[0], 0);
		dup2(fd_write, 1);
		read(0, buffer_2, BUFFER_PIPEX);
		// command 2
		write(1, buffer_2, BUFFER_PIPEX);
		close(1);
	}

	return (0);
}