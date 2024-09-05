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

static void	get_hd_input(int argc, char *argv[], t_fd *fd);

static char	*add_hd_memory(char *str, size_t add_len);

void	here_doc(int argc, char *argv[], char *envp[], t_fd *fd)
{
	(void)envp;
	if (argc < 6)
	{
		ft_putstr_fd("Not enough arguments. Correct input format: \n", 2);
		ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
		ft_putstr_fd("./pipex here_doc LIMITER cmd cmd1 file\n", 2);
		exit(1); // return?
	}
	if (get_delimiter(argv, fd) == 1)
	{
		// freeing
		exit(1); // return?
	}
	fd->cmd_num = argc - 4;
	fd->hd_flag = 1;
	//ft_printf("Commands %d, flag %d\n", fd->cmd_num, fd->hd_flag);
	get_hd_input(argc, argv, fd);
	if (pipe(fd->pipe) == -1) // opening the pipe
	{
		perror("Pipe failed");
		return ;
	}
	ft_putstr_fd(fd->hd_input, fd->pipe[1]);
	free(fd->hd_input);
	fd->hd_input = NULL;
	close(fd->pipe[1]);
	fd->in = fd->pipe[0];
	//exit(0);	// delete
}

static void	get_hd_input(int argc, char *argv[], t_fd *fd)
{
	char	*new_line;

	(void)argv;
	(void)argc;
	new_line = NULL;
	//ft_printf("delim: %s\n", fd->delim);
	ft_printf("pipex: >");
	new_line = get_next_line(0);
	//ft_printf("new_line: %s\n", new_line);
	while (new_line && ft_strncmp(new_line, fd->delim, ft_strlen(fd->delim))) // + check if same length of new_line and delim
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
		new_line = get_next_line(0);
	}
	free(fd->delim);
	fd->delim = NULL;
	if (new_line)
	{
		free(new_line);
		new_line = NULL;
	}
	//ft_printf("Final string: %s", fd->hd_input);
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