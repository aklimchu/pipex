#include "../libft/libft.h"
#include <fcntl.h>

int	main(int argc, char *argv[])
{
	int	fd;
	
	if (argc < 2)
		return (ft_printf("%s\n", "Not enough arguments"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_printf("%s\n", "Error when opening the file"));
	ft_printf("%s\n", get_next_line(fd));
	ft_printf("%s\n", get_next_line(fd));
	ft_printf("%s\n", get_next_line(fd));
	return (0);
}