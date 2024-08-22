/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:45 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/22 12:50:08 by aklimchu         ###   ########.fr       */
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

char	**check_param(char *str, int copy_out)
{
	char	*str_new;
	char	set[3];
	char	**param;

	if (str[0] == '\0' || str[0] == ' ')
	{
		printing_nop(str, ": command not found\n", copy_out);
		exit(127);
	}
	set[0] = '"';
	set[1] = 92;
	set[2] = '\0';
	str_new = str_filter(str, set);
	if (str_new == NULL)
		return(NULL);
/* 	if (str_new[0] == ' ')
	{
		printing_nop(str_new, ": command not found\n", copy_out);
		free(str_new);
		exit(127);
	} */
	param = ft_split_new(str_new, ' ');
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
		is_directory(command, copy_out);
		check_access(param, copy_out);
		return(command);
	}
	
	//---------------getting the path to command--------------------
	path = get_path(envp);
	if (path == NULL)
	{
		printing(command, ": No such file or directory\n", copy_out);
		free_all(param, NULL, NULL);
		exit(127);
	}
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
		printing_nop(command, ": command not found\n", copy_out);
		free_all(NULL, param, NULL);
		exit(127);
	}
	return(full_path);
}

static char	**get_path(char *envp[])
{
	int		i;
	char	**path;

	if (envp == NULL)
	{
		/* path = ft_split("/home/aklimchu/bin:/usr/local/sbin:\
			/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:\
			/usr/local/games:/snap/bin", ':');
		return(path); */
		return(NULL);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return(NULL);
	path = ft_split((envp[i] + 5), ':');
	return(path);
}

static void	check_access(char **param, int copy_out)
{
	char	*command;

	command = param[0];
	/* if (access(command, X_OK) == -1 && errno == EACCES)
	{
		printing(command, "Permission denied", copy_out);
		free_all(param, NULL, NULL);
		exit(126);
	} */
	if (access(command, F_OK) == -1 && errno == ENOENT)
	{
		printing(command, ": No such file or directory\n", copy_out);
		free_all(param, NULL, NULL);
		exit(127);
	}
	return ;
}