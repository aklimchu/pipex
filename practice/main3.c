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

	fd_write = open(argv[4], O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (fd_write == -1)
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
		char buffer[BUFFER_PIPEX + 1];

		nbytes = read(fd_read, buffer, BUFFER_PIPEX + 1);
		if (nbytes == -1)
			exit(1);
		// command 1
		buffer[nbytes] = '\0';
		ft_printf("%s\n", buffer);
		write(fd[1], buffer, nbytes);

		close(fd_read);
		close(fd[1]);
	}

		close(fd_read);
		close(fd[1]);
	//------------------second fork----------------------------------
	
	p2 = fork();
	if (p2 == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	if (p2 == 0) // child process
	{
		char buffer_2[BUFFER_PIPEX + 1];

		int nbytes = read(fd[0], buffer_2, BUFFER_PIPEX + 1);
		buffer_2[nbytes] = '\0';
		// command 2
		ft_printf("%s\n", buffer_2);
		write(fd_write, buffer_2, nbytes);

		close(fd[0]);
		close(fd_write);
	}
	close(fd[0]);
	return (0);
}