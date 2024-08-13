#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	int		fd1[2];
	int		fd2[2];
	
	char	fixed_str[] = "forgeeks.org";
	pid_t	p;

	if (argc > 2)
	{
		printf("Too many arguments\n");
		exit(1);
	}

	if (argc < 2)
	{
		printf("Not enough arguments\n");
		exit(1);
	}

	if (pipe(fd1) == -1)
	{
		perror("Pipe failed");
		exit(1);
	}

	if (pipe(fd2) == -1)
	{
		perror("Pipe failed");
		exit(1);
	}

	p = fork();
	if (p < 0)
	{
		perror("Fork failed");
		exit(1);
	}

	else if (p > 0)
	{
		char	concat_str[100];

		close(fd1[0]);

		write(fd1[1], argv[1], strlen(argv[1]) + 1);
		close(fd1[1]);

		wait(NULL);

		close(fd2[1]);

		read(fd2[0], concat_str, 100);
		printf("Concatenated string %s\n", concat_str);
		close(fd2[0]);
	}

	else
	{
		close(fd1[1]);

		char	concat_str[100];
		read(fd1[0], concat_str, 100);

		int				k = strlen(concat_str);
		unsigned int	i = 0;

		while (i < strlen(fixed_str))
			concat_str[k++] = fixed_str[i++];
		concat_str[k] = '\0';

		close(fd1[0]);
		close(fd2[0]);

		write(fd2[1], concat_str, strlen(concat_str) + 1);
		close(fd2[1]);

		exit(0);
	}
}