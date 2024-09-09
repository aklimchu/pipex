/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:39 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/09 11:33:20 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	check_file_access(char *str);

static int	waiting_for_pids(t_fd *fd);

int	main(int argc, char *argv[], char *envp[])
{
	t_fd	fd;

	if (argc != 5)
	{
		ft_putstr_fd("Incorrect number of arguments. ", 2);
		ft_putstr_fd("Correct input format:\n", 2);
		ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	check_file_access(argv[1]);
	fd.read = open(argv[1], O_RDONLY);
	if (pipe(fd.pipe) == -1)
	{
		perror("Pipe failed");
		return (close(fd.read));
	}
	if (fork_1(argv, envp, &fd) == 1)
		return (1);
	if (fork_2(argv, envp, &fd) == 1)
		return (1);
	if (waiting_for_pids(&fd) == 1)
		return (1);
	if (WIFEXITED(fd.status))
		return (WEXITSTATUS(fd.status));
	return (0);
}

static void	check_file_access(char *str)
{
	if (access(str, R_OK) == -1 && errno == EACCES)
		printing(str, ": Permission denied\n", 2);
	if (access(str, F_OK) == -1 && errno == ENOENT)
		printing(str, ": No such file or directory\n", 2);
}

static int	waiting_for_pids(t_fd *fd)
{
	if (waitpid(fd->p2, &fd->status, 0) == -1)
	{
		perror("wait() error");
		return (1);
	}
	if (waitpid(fd->p1, NULL, 0) == -1)
	{
		perror("wait() error");
		return (1);
	}
	return (0);
}
