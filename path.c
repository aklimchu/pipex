/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:45 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/19 15:57:32 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* int	main(int argc, char *argv[], char *envp[])
{
	char	*path;
	
	path = check_path(envp, argv[1]);
	ft_printf("%s\n", path);
} */

static char **get_path(char *envp[]);

static void	check_access(char **param, int copy_out);

char	**check_param(char *str)
{
	char	*str_new;
	char	set[2];
	char	**param;

	set[0] = '"';
	set[1] = '\0';
	str_new = ft_strtrim(str, set);
	if (str_new == NULL)
		return(NULL);
	param = ft_split(str_new, ' ');
	free(str_new);
	return(param);
}

char	*check_path(char *envp[], char **param, int copy_out)
{
	int		i;
	char	*full_path;
	char	**path;
	char	*command;
	
	command = param[0];
	/* if (access(command, F_OK) == 0)	//what if there is no permissions to execute?
		return(command); */
	//-----------------checking if input is directory---------------
	if (ft_strrchr(command, '/'))
	{
		check_access(param, copy_out);
		return(command);
	}
	path = get_path(envp);
	if (path == NULL)
		return(NULL);
	i = 0;
	while (path[i])
	{
		full_path = ft_strjoin_new(path[i], "/", command);
		if (full_path == NULL)
			break ;
		if (access(full_path, F_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_all(path, NULL, NULL);
	if (full_path == NULL)
	{
		ft_putstr_fd("pipex: ", copy_out);
		ft_putstr_fd(command, copy_out);
		ft_putstr_fd(": command not found\n", copy_out);
		free_all(NULL, param, NULL);
		exit(127);
	}
	return(full_path);
}

static char	**get_path(char *envp[])
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
	return(path);
}

static void	check_access(char **param, int copy_out)
{
	char	*command;

	command = param[0];
	if (access(command, X_OK) == -1 && errno == EACCES) // not working properly
	{
		ft_putstr_fd("pipex: ", copy_out);
		ft_putstr_fd(command, copy_out);
		ft_putstr_fd(": permission denied\n", copy_out);
		//ft_printf("pipex: %s: permission denied\n", command);
		free_all(param, NULL, NULL);
		exit(126);
	}
	if (access(command, F_OK) == -1 && errno == ENOENT)
	{
		ft_putstr_fd("pipex: ", copy_out);
		ft_putstr_fd(command, copy_out);
		ft_putstr_fd(": no such file or directory\n", copy_out);
		//ft_printf("pipex: %s: no such file or directory\n", command);
		free_all(param, NULL, NULL);
		exit(127);
	}
	return ;
}