/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:45 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/02 08:08:18 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	**get_path(char *envp[]);

static void	str_new_print(char *str, char *str_new);

static char	*get_full_path(char **path, char *command, char **param);

char	**check_param(char *str)
{
	char	*str_new;
	char	set[3];
	char	**param;
	int		word_num;

	if (str[0] == '\0' || str[0] == ' ')
	{
		printing_nop(str, ": command not found\n", 2);
		exit(127);
	}
	set[0] = '"';
	set[1] = 92;
	set[2] = '\0';
	str_new = str_filter(str, set);
	if (str_new == NULL)
		return (NULL);
	if (str_new[0] == '\0')
		str_new_print(str, str_new);
	word_num = count_param(str_new);
	param = ft_split_new(str_new, ' ', word_num);
	free(str_new);
	return (param);
}

char	*check_path(char *envp[], char **param)
{
	char	*full_path;
	char	**path;
	char	*command;

	command = param[0];
	if (ft_strrchr(command, '/')) // checking if input is a directory
	{
		is_directory(command);
		check_command_access(param);
		return (command);
	}
	path = get_path(envp); // getting path to the command
	if (path == NULL)
	{
		printing(command, ": No such file or directory\n", 2);
		free_all(param, NULL, NULL);
		exit(127);
	}
	full_path = get_full_path(path, command, param);
	return (full_path);
}

static char	**get_path(char *envp[])
{
	int		i;
	char	**path;

	path = NULL;
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (path);
}

static void	str_new_print(char *str, char *str_new)
{
	printing_nop(str, ": command not found\n", 2);
	free_all(NULL, NULL, str_new);
	exit(127);
}

static char	*get_full_path(char **path, char *command, char **param)
{
	char	*full_path;
	int		i;

	full_path = NULL;
	i = 0;
	while (path[i])
	{
		full_path = ft_strjoin_new(path[i], "/", command);
		if (full_path && access(full_path, F_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_all(path, NULL, NULL);
	if (full_path == NULL)
	{
		printing_nop(command, ": command not found\n", 2);
		free_all(NULL, param, NULL);
		exit(127);
	}
	return (full_path);
}
