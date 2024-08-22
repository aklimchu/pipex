#include "../pipex.h"
#define PATH_MAX 4096

int	main(void)
{
	int fd = open("/proc/self/environ", O_RDONLY);

	char	*buffer = (char *)malloc(PATH_MAX * sizeof(char));

	ssize_t n = read(fd, buffer, PATH_MAX - 1);
	buffer[n] = '\0';

	close(fd);

	ft_printf("%s\n", buffer);
	return (0);
}