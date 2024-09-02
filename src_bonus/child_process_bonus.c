/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:20:07 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/02 08:08:38 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

/* static int	argv_count(char **argv)
{
	int	count;

	count = 0;
	while(argv[count])
		count++;
	ft_printf("count %d\n", count);
	return(count - 1);
} */

void	child_process(char *argv[], char **envp, t_fd fd, int i)
{
	char	*path_1;
	char	**param_1;
	
	close(fd.pipe[i][0]);
	
	if (fd.in == -1 && i == 0)
	{
		close(fd.pipe[i][1]);
		exit(1);
	}
	else if (fd.in != -1)
	{
		dup2(fd.in, 0);
		close(fd.in);
	}
	else
		dup2(fd.pipe[i - 1][0], 0);
		
	if (i > 0)
		close(fd.pipe[i - 1][0]);
	
	dup2(fd.pipe[i][1], 1);
	close(fd.pipe[i][1]);
				
	param_1 = check_param(argv[i + 2]);
	if (param_1 == NULL)
		exit(1);
		
	path_1 = check_path(envp, param_1);
	if (path_1 == NULL)
	{
		free_all(param_1, NULL, NULL);
		exit(1);
	}
	if (execve(path_1, param_1, envp) == -1)
	{
		printing(param_1[0], ": Permission denied\n", 2);
		free_all(param_1, NULL, NULL);	// freeing path_1?
		exit(126);
	}
	free_all(param_1, NULL, path_1);
	exit(0);
}