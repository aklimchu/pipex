/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:11:02 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/05 13:46:12 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static int		get_delimiter(char *argv[], t_fd *fd);

static int		get_hd_input(t_fd *fd);

static char		*new_hd_input(char **hd_input, char **new_line);

static char		*add_hd_memory(char *str, size_t add_len);

int	here_doc(int argc, char *argv[], t_fd *fd)
{
	if (argc < 6)
	{
		ft_putstr_fd("Not enough arguments. Correct input format: \n", 2);
		ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
		ft_putstr_fd("./pipex here_doc LIMITER cmd cmd1 file\n", 2);
		return (1);
	}
	if (get_delimiter(argv, fd) == 1)
		return (1);
	fd->cmd_num = argc - 4;
	fd->hd_flag = 1;
	if (get_hd_input(fd) == 1)
		return (free_str(fd->hd_input, NULL));
	if (pipe(fd->pipe) == -1)
	{
		perror("Pipe failed");
		return (free_str(fd->hd_input, NULL));
	}
	ft_putstr_fd(fd->hd_input, fd->pipe[1]);
	free_str(fd->hd_input, NULL);
	close(fd->pipe[1]);
	fd->in = fd->pipe[0];
	return (0);
}

static int	get_delimiter(char *argv[], t_fd *fd)
{
	fd->delim = ft_strdup(argv[2]);
	if (fd->delim == NULL)
	{
		perror("malloc() failed");
		return (1);
	}
	return (0);
}

static int	get_hd_input(t_fd *fd)
{
	char	*new_line;

	new_line = NULL;
	fd->hd_input = ft_strdup("");
	if (fd->hd_input == NULL)
	{
		perror("malloc() failed");
		return (1);
	}
	ft_printf("pipex: >");
	new_line = get_next_line(0);
	while (new_line)
	{
		if (!ft_strncmp(new_line, fd->delim, ft_strlen(fd->delim)) && \
			ft_strchr_fix(new_line, '\n') == ft_strlen(fd->delim))
			break ;
		if (new_hd_input(&fd->hd_input, &new_line) == NULL)
			return (free_str(new_line, NULL));
	}
	free_str(fd->delim, new_line);
	return (0);
}

static char	*new_hd_input(char **hd_input, char **new_line)
{
	*hd_input = add_hd_memory(*hd_input, ft_strlen(*new_line));
	if (*hd_input == NULL)
	{
		perror("malloc() failed");
		return (NULL);
	}
	*hd_input = ft_strncat(*hd_input, *new_line, \
			ft_strlen(*hd_input) + ft_strlen(*new_line) + 1);
	free_str(*new_line, NULL);
	ft_printf("pipex: >");
	*new_line = get_next_line(0);
	return ("");
}

static char	*add_hd_memory(char *str, size_t add_len)
{
	char	*temp;
	size_t	old_len;

	if (str == NULL)
		str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	old_len = ft_strlen(str);
	temp = (char *)malloc(old_len + add_len + 1);
	if (temp == NULL)
		return (NULL);
	while (*str)
	{
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	free(str - old_len);
	return (temp - old_len);
}
