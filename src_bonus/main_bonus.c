/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:39 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/04 15:16:59 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static int	check_file_and_argc(int argc, char *argv[], char *envp[]);

static int	waiting_for_pids(t_fd *fd, int argc, int count);

int	main(int argc, char *argv[], char *envp[])
{
	t_fd	fd;
	int		i;

	if (check_file_and_argc(argc, argv, envp) == 1)
		return (1);
	fd.null = NULL; // mention for here_doc?
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
	close_free(fd.in, -1, -1, &fd.null);
	if (last_fork(&fd, argv, envp, i) == 1 || \
		waiting_for_pids(&fd, argc, i) == 1)
		return (free_pid(&fd.pid));
	free_pid(&fd.pid);
	if (WIFEXITED(fd.status))
		return (WEXITSTATUS(fd.status));
	return (0);
}

static int	check_file_and_argc(int argc, char *argv[], char *envp[])
{
	if (argc < 5)
	{
		ft_putstr_fd("Not enough arguments. Correct input format: \n", 2);
		ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
		ft_putstr_fd("./pipex here_doc LIMITER cmd cmd1 file\n", 2);
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
		here_doc(argc, argv, envp);
	if (access(argv[1], R_OK) == -1 && errno == EACCES)
		printing(argv[1], ": Permission denied\n", 2);
	if (access(argv[1], F_OK) == -1 && errno == ENOENT)
		printing(argv[1], ": No such file or directory\n", 2);
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
