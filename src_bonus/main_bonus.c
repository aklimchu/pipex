/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:39 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/03 14:22:46 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static int	check_file_and_argc(char *str, int argc);

static int	waiting_for_pids(t_fd *fd, int argc, int count);

int	main(int argc, char *argv[], char *envp[])
{
	t_fd	fd; // fd.pid is not freed correctly e.g. if first file doesn't exist or command is not found)
	int		i;
	
	if (check_file_and_argc(argv[1], argc) == 1)
		return (1);	
	fd.pid = (pid_t *)malloc((argc - 3) * sizeof(pid_t));
	if (fd.pid == NULL)
		return (1);	
	fd.in = open(argv[1], O_RDONLY); // opening the file
	i = 0;
	while (i == 0 || i < argc - 4)
	{
		if (pipe_and_fork(&fd, argv, envp, i) == 1) // all forks except for the last one
			return (free_pid(&fd.pid));
		i++;
	}
	close_fds(fd.in, -1, -1);
	if (last_fork(&fd, argv, envp, i) == 1 ||\
		waiting_for_pids(&fd, argc, i) == 1)
		return (free_pid(&fd.pid));
	free_pid(&fd.pid);
	if (WIFEXITED(fd.status))
		return (WEXITSTATUS(fd.status));
	return (0);
}

static int	check_file_and_argc(char *str, int argc)
{
	if (argc < 5)
	{
		ft_putstr_fd("Not enough arguments. Correct input format: ", 2);
		ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	if (access(str, R_OK) == -1 && errno == EACCES)
		printing(str, ": Permission denied\n", 2);
	if (access(str, F_OK) == -1 && errno == ENOENT)
		printing(str, ": No such file or directory\n", 2);
	return (0);
}

static int	waiting_for_pids(t_fd *fd, int argc, int count)
{
	if (waitpid((*fd).pid[count], &(*fd).status, 0) == -1)
	{
		perror("wait() error");
		return (1);
	}
	count = 0;
	while (count < argc - 4)
	{
		if (waitpid((*fd).pid[count], NULL, 0) == -1)
		{
			perror("wait() error");
			return (1);
		}
		count++;
	}
	return (0);
}
