#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	//int		i;
	int		fd[2];
	int		nbytes;
	pid_t	p1;
	//pid_t	p2;
	int		fd_read;
	int		fd_write;
	char	*str_new;

	(void)envp;
	str_new = (char *)malloc((BUFFER_SIZE + 4) * sizeof(char));
	if (str_new == NULL)
		exit(1);
	/* while (envp[i])
		ft_printf("%s\n", envp[i++]);
 */

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
	if (fd_read < 0)
	{
		perror("Opening the file failed");
		exit(1);
	}
	dup2(fd_read, 0);
	fd_write = open(argv[4], O_WRONLY);
	if (fd_write < 0)
	{
		perror("Opening the file failed");
		exit(1);
	}
	dup2(fd_write, 1);

	//------------------opening the pipe----------------------------
	if (pipe(fd) == -1)
	{
		perror("Pipe failed");
		exit(1);
	}
	
	//------------------first fork----------------------------------
	p1 = fork();
	if (p1 < 0)
	{
		perror("Fork failed");
		exit(1);
	}

	if (p1 == 0) // child process
	{
		char buffer[BUFFER_SIZE + 1];
		
		nbytes = read(0, buffer, BUFFER_SIZE);
		if (nbytes == -1)
			exit(1);
		write(fd[1], buffer, BUFFER_SIZE);
	}
	else  // parent process
{
		char str[BUFFER_SIZE + 1];
		read(fd[0], str, BUFFER_SIZE);
		str_new = ft_strjoin(str, "HEY");
		//ft_printf("%s\n", str_new);
		write(1, str_new, BUFFER_SIZE + 4);
	

	//------------------second fork----------------------------------
	/*p2 = fork();
	if (p2 < 0)
	{
		perror("Fork failed");
		exit(1);
	}

	if (p2 == 0) // child process
	{
		//close(fd[0]);
		write(fd[1], str_new, BUFFER_SIZE + 3);
		close(fd[1]);
	}
	else // parent process
	{
		char	*str2;
		char	*str_new2;
		close(fd[1]);
		read(fd[0], str2, BUFFER_SIZE + 3);
		str_new2 = ft_strjoin(str2, "MOI");
		close(fd[0]);
		write(1, str_new2, BUFFER_SIZE + 6);
	}*/
}
	free(str_new);
	//-------------------closing the files---------------------------
	close(0);
	close(1);

	return (0);
}