/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:39 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/02 09:24:47 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	check_file_access(char *str);

int	main(int argc, char *argv[], char *envp[])
{
	t_fd	fd;

	if (argc == 1)	// first arg
		return(1);
	check_file_access(argv[1]);
	if (argc == 2)	//second arg
		return(1);
	fd.read = open(argv[1], O_RDONLY);	//reading the file
	if (pipe(fd.pipe) == -1)	// opening the pipe
	{
		perror("Pipe failed");
		return(close(fd.read));
	}
	if (fork_1(argv, envp, &fd) == 1)
		return(1);
	if (argc == 3)	//third arg
		return(close(fd.pipe[0]));
	if (fork_2(argv, envp, &fd) == 1)
		return(1);
	waitpid(fd.p2, &fd.status, 0);
	waitpid(fd.p1, NULL, 0);
	if (WIFEXITED(fd.status))
		return (WEXITSTATUS(fd.status));
	return (0);
}

static void	check_file_access(char *str)
{
	if (access(str, R_OK) == -1 && errno == EACCES)
		ft_printf("pipex: %s: Permission denied\n", str);
	if (access(str, F_OK) == -1 && errno == ENOENT)
		ft_printf("pipex: %s: No such file or directory\n", str);
}
