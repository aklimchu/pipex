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
		dup2(fd_read, 0);
		dup2(fd[1], 1);
		
		//parse_command_path

		close(0);
		close(1);
	}
	// waitpid(0, NULL, 0);
	close(0);
	close(1);

	//------------------second fork----------------------------------
	p2 = fork();
	if (p2 == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	if (p2 == 0) // child process
	{
		fd_write = open(argv[4], O_WRONLY);
		if (fd_write == -1)
		{
			perror("Opening the file failed");
			exit(1);
		}
		
		dup2(fd[0], 0);
		dup2(fd_write, 1);
	
		// command 2

		close(0);
		close(1);
	}
	// waitpid(0, NULL, 0);
	close(0);
	return (0);
}