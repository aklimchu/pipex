/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:45 by aklimchu          #+#    #+#             */
/*   Updated: 2024/08/16 12:44:29 by aklimchu         ###   ########.fr       */
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

char	**check_param(char *str)
{
	char	*str_new;
	char	set[2];
	char	**param;

	set[0] = '"';
	set[1] = '\0';
	str_new = ft_strtrim(str, set);	// protect malloc?
	param = ft_split(str_new, ' ');	// protect malloc?
	free(str_new);
	return(param);
}

char	*check_path(char *envp[], char *command)
{
	int		i;
	char	*full_path;
	char	**path;

	path = get_path(envp);
	i = 0;
	while (path[i])
	{
		full_path = ft_strjoin_new(path[i], "/", command);		//protect malloc?
		if (access(full_path, F_OK) == 0)
			break;	// free array PATH and return full_path?
		free(full_path);
		full_path = NULL;
		i++;
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
 */	path = ft_split((envp[i] + 5), ':');	//protect malloc?
	i = 0;
	return(path);
}

