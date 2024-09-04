/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:11:02 by aklimchu          #+#    #+#             */
/*   Updated: 2024/09/04 16:03:22 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	get_hd_input(char *argv[], t_fd *fd);

static char	*add_hd_memory(char *str, size_t add_len);

void	here_doc(int argc, char *argv[], char *envp[])
{
	t_fd	fd;

	(void)envp;
	if (argc < 6)
	{
		ft_putstr_fd("Not enough arguments. Correct input format: \n", 2);
		ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
		ft_putstr_fd("./pipex here_doc LIMITER cmd cmd1 file\n", 2);
		exit(1);
	}
	fd.null = NULL;
	fd.hd_input = NULL;
	if (get_delimiter(argv, &fd) == 1)
	{
		// freeing
		exit(1);
	}
	get_hd_input(argv, &fd);
	exit(0);
}

static void	get_hd_input(char *argv[], t_fd *fd)
{
	char	*new_line;

	(void)argv;
	new_line = NULL;
	//ft_printf("delim: %s\n", fd->delim);
	ft_printf("pipex: >");
	new_line = get_next_line(0);
	//ft_printf("new_line: %s\n", new_line);
	while (ft_strncmp(new_line, fd->delim, ft_strlen(fd->delim))) // + check if same length of new_line and delim
	// Ctrl + d?
	{
		fd->hd_input = add_hd_memory(fd->hd_input, ft_strlen(new_line));
		if (fd->hd_input == NULL)
		{
			//freeing memory
			exit(1);
		}
		fd->hd_input = ft_strncat(fd->hd_input, new_line, ft_strlen(fd->hd_input) + \
			ft_strlen(new_line) + 1);
		free(new_line);
		new_line = NULL;
		ft_printf("pipex: >");
		new_line = get_next_line(0); // freeing new_line
	}
	ft_printf("Final string: %s", fd->hd_input);
}

static char	*add_hd_memory(char *str, size_t add_len)
{
	char	*temp;
	size_t	old_len;

	if (str == NULL)
		str = ft_strdup("");
	if (str == NULL)
		return (NULL); // freeing memory?
	old_len = ft_strlen(str);
	temp = (char *)malloc(old_len + add_len + 1);
	if (temp == NULL)
		return (NULL); // freeing memory?
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