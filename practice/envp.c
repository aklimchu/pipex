#include <stdio.h>
#include "/home/aklimchu/pipex/pipex.h"

char **get_path(char *envp[]);

int	main(int argc, char *argv[], char *envp[])
{
	int i = 0;
	char	**path;
	
	/* while (envp[i])
		printf("%s\n", envp[i++]); */
/* 	printf("%s\n", envp[30]);
 */	path = get_path(envp);
	while (path[i])
		printf("%s\n", path[i++]);
}

char **get_path(char *envp[])
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
/* 	ft_printf("%s\n", envp[i]);
 */	path = ft_split((envp[i] + 5), ':');
	i = 0;
	return(path);
}